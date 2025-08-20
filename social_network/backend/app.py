from flask import Flask, jsonify, request,send_from_directory
from flask_cors import CORS  # 允许跨域请求
import os
import math
import json
import networkx as nx

# 创建 Flask 应用
app = Flask(__name__)
CORS(app)  # 启用跨域支持

# --------------------------
# 前端部署部分
# --------------------------
# static_folder 指向 Vue build 出来的 dist 文件夹
app = Flask(__name__, static_folder="../dist", static_url_path="/")

@app.route("/")
def index():
    return send_from_directory(app.static_folder, "index.html")
# 如果前端是单页应用（SPA），处理路由刷新问题
@app.errorhandler(404)
def not_found(e):
    return send_from_directory(app.static_folder, "index.html")


global json_data  # 全局变量存储 JSON 数据
json_data = None

def load_data():
    # 从 JSON 文件加载社交网络数据(带异常处理),并创建networkx图对象
    global json_data  # 全局变量存储 JSON 数据
    try:
        if json_data:  # 如果全局变量有数据，直接使用
            data = json_data
        else:          # 否则读取默认文件
            with open('../public/default-data.json', 'r', encoding='utf-8') as f:
                data = json.load(f)
        
        G = nx.Graph()
        # 添加节点和边
        for node in data['nodes']:
            attrs = {
                'name': node.get('name', ''),
                'symbolSize': node.get('symbolSize'), 
                'category': node.get('category'),
                'schools': [],
                'companies': [],
                'groups': [],
                'region': None  # 单值属性初始为 None
            }
            G.add_node(node['id'], **attrs)
        for link in data["links"]:
            G.add_edge(link["source"], link["target"])

        # 添加人物节点的属性信息
        # 定义 category 到属性名的映射
        CATEGORY_TO_ATTR = {
        1: 'schools',    # 多值
        2: 'region',     # 单值
        3: 'companies',  # 多值
        4: 'groups'      # 多值
        }
        for person_id in G.nodes():
            if G.nodes[person_id].get('category') == 0:
                for neighbor_id in G.neighbors(person_id):
                    neighbor_category = G.nodes[neighbor_id].get('category')
                    neighbor_name = G.nodes[neighbor_id].get('name', '')

                    if neighbor_category in CATEGORY_TO_ATTR:
                        attr_name = CATEGORY_TO_ATTR[neighbor_category]
                        if attr_name == 'region':
                            G.nodes[person_id][attr_name] = neighbor_name  # 单值直接覆盖
                        else:
                            G.nodes[person_id][attr_name].append(neighbor_name) 
        return G
    except Exception as e:
        print(f"Error loading JSON: {e}")
        return {"nodes":[],"links":[],"categories":[]}#返回三个数组

# --------------------------
# 推荐算法实现部分
# --------------------------
def get_person_neighbors(G, node_id):
    """获取person类别的邻居节点（根据category=0判断）"""
    return [
        n for n in G.neighbors(node_id) 
        if G.nodes[n].get('category') == 0  # 根据您的数据，person的category是0
    ]

# 定义类别权重 (侧重共同好友)
global WEIGHTS
WEIGHTS = {
    'schools':1.5,
    'groups': 1.5,
    'region': 1.0,
    'companies': 1.5,
    'friends': 5.0
}

def calc_weighted_intersection(G, u, v):
    """
    加权交集算法
    公式: ∑(w_k * N_k),其中w_k是类别权重,N_k是共同属性数
    """
    
    score = 0
    # 1. 共同学校
    common_schools = set(G.nodes[u]['schools']) & set(G.nodes[v]['schools'])
    score += WEIGHTS['schools'] * len(common_schools)   
    # 2. 共同群组
    common_groups = set(G.nodes[u]['groups']) & set(G.nodes[v]['groups'])
    score += WEIGHTS['groups'] * len(common_groups)
    # 3. 共同地区
    # common_region = set(G.nodes[u]['region']) & set(G.nodes[v]['region'])
    # score += WEIGHTS['region'] * len(common_region)
    region_u = G.nodes[u]['region']
    region_v = G.nodes[v]['region']
    common_region = set()
    if region_u is not None and region_v is not None:
        common_region = {region_u} & {region_v}  # 单值比较
    score += WEIGHTS['region'] * len(common_region)
    # 4. 共同公司
    common_companies = set(G.nodes[u]['companies']) & set(G.nodes[v]['companies'])
    score += WEIGHTS['companies'] * len(common_companies)
    # 5. 共同好友
    common_friends = set(get_person_neighbors(G, u)) & set(get_person_neighbors(G, v))
    score += WEIGHTS['friends'] * len(common_friends)
    
    return score

def calc_weighted_union(G, u, v):
    """
    计算加权并集
    公式: ∑(w_k * N_k),其中w_k是类别权重,N_k是共同属性数
    """
    
    score = 0
    # 1. 学校并集
    union_schools = set(G.nodes[u]['schools']) | set(G.nodes[v]['schools'])
    score += WEIGHTS['schools'] * len(union_schools)  
    # 2. 群组并集
    union_groups = set(G.nodes[u]['groups']) | set(G.nodes[v]['groups'])
    score += WEIGHTS['groups'] * len(union_groups)
    # 3. 地区并集
    # union_region = set(G.nodes[u]['region']) | set(G.nodes[v]['region'])
    # score += WEIGHTS['region'] * len(union_region)
    region_u = G.nodes[u]['region']
    region_v = G.nodes[v]['region']
    common_region = set()
    if region_u is not None and region_v is not None:
        common_region = {region_u} | {region_v}  # 单值比较
    score += WEIGHTS['region'] * len(common_region)
    # 4. 公司并集
    union_companies = set(G.nodes[u]['companies']) | set(G.nodes[v]['companies'])
    score += WEIGHTS['companies'] * len(union_companies)
    # 5. 好友并集
    union_friends = set(get_person_neighbors(G, u)) | set(get_person_neighbors(G, v))
    score += WEIGHTS['friends'] * len(union_friends)
    return score

def calc_jaccard_improved(G, u, v):
    """
    加权Jaccard算法
    """
    intersection = calc_weighted_intersection(G, u, v)
    union = calc_weighted_union(G, u, v)
    
    return intersection / union if union > 0 else 0

def calc_adamic_adar(G, u, v):
    """
    Adamic-Adar算法
    公式: ∑(1/log(好友w的度数)) , w是共同好友
    """
    score = 0
    for w in set(get_person_neighbors(G, u)) & set(get_person_neighbors(G, v)):
        degree = len(get_person_neighbors(G, w))
        if degree > 1:  # 避免log(1)=0
            score += 1 / math.log(degree)
    return score

# --------------------------
# Flask路由
# --------------------------
@app.route('/api/initdata')
def init_data():
    if json_data:
        return json_data
    else:
        print('Using default JSON data')
        try:
            with open('../public/default-data.json', 'r', encoding='utf-8') as f:
                data = json.load(f)
            return data
        except Exception as e:
            return jsonify({"error": str(e)}), 500
  
       
    

@app.route('/api/recommend/<user_id>')
def recommend(user_id):
    """推荐可能认识的人"""
    G = load_data()
    
    if user_id not in G.nodes:
        return jsonify({"error": "ID不存在"}), 404
    if G.nodes[user_id].get('category')!=0:
        return jsonify({"error":"此节点ID不在正确范围内"}),404
    
    # 获取用户的直接好友（用于后续过滤）
    user_friends = set(get_person_neighbors(G, user_id))

    candidates = {}
    for candidate_id in G.nodes:
        if (candidate_id != user_id 
            and G.nodes[candidate_id].get("category") == 0
            and not G.has_edge(user_id, candidate_id)):

            # 计算共同好友
            candidate_friends = set(get_person_neighbors(G, candidate_id))
            common_friends = user_friends & candidate_friends
            scores = {
                'weighted': calc_weighted_intersection(G, user_id, candidate_id),
                'jaccard': calc_jaccard_improved(G, user_id, candidate_id),
                'adamic': calc_adamic_adar(G, user_id, candidate_id),
                'final': 0 , # 待计算
            }
            # 加权综合评分 (权重可调)
            scores['final'] = (
                0.4 * scores['weighted'] + 
                0.3 * scores['jaccard'] + 
                0.3 * scores['adamic']
            )
            common_friends_count = len(common_friends)

            candidates[candidate_id] = {
                'id':candidate_id,
                'name': G.nodes[candidate_id]['name'],
                'scores': scores,
                'common_friends': common_friends_count
            }
    
    # 按综合分排序
    sorted_candidates = sorted(
        candidates.values(), 
        key=lambda x: -x['scores']['final']
    )
    
    response = jsonify({
        'user': G.nodes[user_id]['name'],
        'recommendations': sorted_candidates[:20]  # 返回Top20
    })
    response.headers.add('Access-Control-Allow-Origin', '*')  # 手动添加头进行跨域
    return response

@app.route('/api/handle-node-info', methods=['POST'])
def node_info():
    data = request.get_json()
    node_id = data.get('nodeId')
    G = load_data()    
    #返回该节点：
    if node_id not in G.nodes:
        return jsonify({"error": "节点不存在"}), 404
    node_data = G.nodes[node_id]
    # 构建返回数据
    response_data = {
        'id': node_id,
        'name': node_data.get('name', ''),
        'category': node_data.get('category'),
        'schools': node_data.get('schools', []),
        'companies': node_data.get('companies', []),
        'groups': node_data.get('groups', []),
        'region': node_data.get('region')
    }
    # 返回JSON响应
    return jsonify(response_data)

@app.route('/api/upload-json', methods=['POST'])
def upload_json():
    if 'file' not in request.files:
        return jsonify({"error": "No file part"}), 400
    
    file = request.files['file']
    if file.filename == '':
        return jsonify({"error": "No selected file"}), 400
    
    if file and file.filename.endswith('.json'):
        try:
            global json_data 
            old_json_data = json_data  # 保存旧数据
            json_data = json.load(file.stream)
            # 检查 JSON 结构是否包含 'nodes' 和 'links'和 'categories'
            if 'nodes' not in json_data or 'links' not in json_data or 'categories' not in json_data:
                json_data = old_json_data  # 恢复旧数据
                return jsonify({"error": "错误的JSON格式: 缺少 'nodes' 或 'links' 或 'categories'"}), 400
            
            return jsonify({
                "status": "success",
                "filename": file.filename
            })
        except json.JSONDecodeError as e:
            return jsonify({"error": "Invalid JSON file", "details": str(e)}), 400
    
    return jsonify({"error": "Invalid file type"}), 400


if __name__ == '__main__':
    port = int(os.environ.get("PORT", 5000))
    app.run(host="0.0.0.0", port=port)

