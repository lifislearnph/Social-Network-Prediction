export function convertToEChartsFormat(rawData) {
  // 1.转换节点,rawData为JSON格式
  const nodes = rawData.nodes.map(node => ({
    id: node.id,
    name: node.name,  
    symbolSize: node.symbolSize,
    category: node.category,
    value: node.value,
    ...node
  }));
  //2. 转换关系链接
  const links = rawData.links.map(link => ({
    source: link.source,
    target: link.target
  }));

   // 3.转换categories格式
  const categories = rawData.categories.map(cat => ({
    name: cat.name
  }));

  const youId = 'user_you'; //中心用户ID,之后改为鼠标选中的ID


  return { nodes, links,categories };
}