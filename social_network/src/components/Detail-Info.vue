<template>
  <div ref="detail-info" class="sidebar-right">
    <div v-if="nodeData">
      <h3>{{ nodeData.name }}</h3>
      <p>ID: {{ nodeData.id }}</p>
      <div v-if="nodeData.category === 0">
        <p>地区: {{ nodeData.region }}</p>
        <p>学校: {{ nodeData.schools }}</p>
        <p>工作单位: {{ nodeData.companies }}</p>
        <p>兴趣社团: {{ nodeData.groups }}</p>
      </div>
    </div>
    <div v-else>
      <p>请点击图中的节点查看详情</p>
    </div>
  </div>
</template>

<script>
export default {
  props: {
    nodeData: {
      type: Object,
      default: null,
    },
  },
}
</script>
