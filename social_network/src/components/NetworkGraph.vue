<template>
  <div ref="chart" class="main" @click="handleClick"></div>
</template>

<script>
import * as echarts from 'echarts'
import { convertToEChartsFormat } from '../utils/convertJsonData.js'
import axios from 'axios'

//画图组件
export default {
  data() {
    return {
      chart: null,
    }
  },

  async mounted() {
    try {
      // 1. 异步加载数据
      const res = await fetch('https://social-network-predictation-backend.onrender.com/api/initdata')
      if (!res.ok) throw new Error('数据加载失败')

      const rawData = await res.json()

      // 2. 转换数据
      const graphData = convertToEChartsFormat(rawData)

      // 3. 渲染图表
      this.chart = echarts.init(this.$refs.chart)
      this.chart.setOption({
        series: [
          {
            type: 'graph',
            layout: 'force',
            force: {
              repulsion: 250,
              edgeLength: 150,
            },
            label: {
              //节点名称显示设置
              show: true,
              position: 'right',
              formatter: '{b}',
              fontSize: 12,
            },
            data: graphData.nodes,
            links: graphData.links,
            categories: [
              { name: 'persons', itemStyle: { color: '#FF6B6B' } },
              { name: 'schools', itemStyle: { color: '#4ECDC4' } },
              { name: 'region', itemStyle: { color: '#43b3ff' } },
              { name: 'companies', itemStyle: { color: '#FFE66D' } },
              { name: 'clubs', itemStyle: { color: '#6A0572' } },
            ],
            //缩放
            roam: true,
            //高亮：
            emphasis: {
              focus: 'adjacency', //只高亮相邻节点和边
              lineStyle: {
                width: 5,
              },
              label: {
                show: true,
                fontWeight: 'bold',
              },
            },
            //模糊化：
            blur: {
              itemStyle: { opacity: 0.1 },
              label: { show: false },
            },
          },
        ],
        //图例：
        legend: {
          data: ['persons', 'schools', 'region', 'companies', 'clubs'],
          selectedMode: false, //禁止选择
          show: true,
          orient: 'vertical',
          left: 'left',
        },
        //在图标下方打印文字提示框：
        title: {
          text: '使用鼠标滚轮进行缩放',
          left: 'center',
          bottom: 0,
          textStyle: {
            fontSize: 14,
            color: '#888',
            fontWeight: 'normal',
          },
        },
      })
      //4.监听鼠标点击事件
      this.chart.on('click', (params) => {
        this.handleNodeClick(params) // 箭头函数保留this上下文
      })
    } catch (error) {
      console.error('图表初始化失败:', error)
    }
  },

  methods: {
    async handleNodeClick(params) {
      if (params.dataType === 'node') {
        console.log('点击的节点信息:', params.data)
        const nodeId = params.data.id
        //到后端查询节点具体信息
        const response = await axios.post('https://social-network-predictation-backend.onrender.com/api/handle-node-info', { nodeId })

        return this.$emit('node-click', response.data)
      }
    },
  },
}
</script>
