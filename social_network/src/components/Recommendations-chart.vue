<template>
  <div ref="recmdResult" class="sidebar-left">
    <h2>可能认识的人</h2>
    <div class="input-box">
      <label for="userId">选择用户 ID：</label>
      <input
        id="userId"
        type="number"
        v-model.number="selectedUserId"
        min="1"
        max="100"
        @keyup.enter="fetchRecommendations"
      />
      <button @click="fetchRecommendations">获取推荐</button>
    </div>
    <p>当前用户名字：{{ selectedUseName }}</p>

    <p v-if="errorMessage" style="color: red">{{ errorMessage }}</p>

    <table v-if="recommendations.length">
      <thead>
        <tr>
          <th>推荐用户ID</th>
          <th>推荐用户姓名</th>
          <th>推荐分数</th>
          <th>共同好友数</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="user in recommendations" :key="user.id">
          <td>{{ user.id }}</td>
          <td>{{ user.name }}</td>
          <td>{{ user.scores.final.toFixed(2) }}</td>
          <td>{{ user.common_friends }}</td>
        </tr>
      </tbody>
    </table>
    <p>*推荐分数越高，表示当前用户与推荐用户认识的可能性越高</p>
  </div>
</template>

<script>
export default {
  data() {
    return {
      selectedUserId: null,
      selectedUseName: '',
      recommendations: [],
      errorMessage: null,
    }
  },
  methods: {
    async fetchRecommendations() {
      this.errorMessage = null
      this.recommendations = []
      try {
        const res = await fetch(`http://localhost:5000/api/recommend/${this.selectedUserId}`)
        if (!res.ok) {
          throw new Error('网络错误或用户 ID 不存在')
        }
        const data = await res.json()
        this.recommendations = data.recommendations
        this.selectedUseName = data.user
      } catch (err) {
        console.error('获取推荐结果失败:', err)
        this.errorMessage = `获取推荐结果失败: ${err.message}`
      }
    },
  },
}
</script>
