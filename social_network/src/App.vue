<template>
  <div id="app">
    <h1 class="header-mid">社交关系网络模拟图</h1>
    <NetworkGraph @node-click="handleNodeClick" />
    <Recommendations-chart />
    <Detail-Info :nodeData="NodeDetail" />
    <div class="footer-right">
      <Upload />
    </div>
  </div>
</template>

<script>
import NetworkGraph from './components/NetworkGraph.vue'
import RecommendationsChart from './components/Recommendations-chart.vue'
import DetailInfo from './components/Detail-Info.vue'
import Upload from './components/Upload.vue'

export default {
  components: { NetworkGraph, RecommendationsChart, DetailInfo, Upload },
  data() {
    return {
      NodeDetail: null,
    }
  },
  methods: {
    handleNodeClick(nodeData) {
      this.NodeDetail = nodeData
    },
  },
}
</script>
