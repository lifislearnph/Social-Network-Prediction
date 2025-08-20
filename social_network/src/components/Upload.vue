<template>
  <div class="file-upload-container">
    <!-- 拖放区域 -->
    <div
      class="drop-zone"
      @dragover.prevent="dragOver = true"
      @dragleave="dragOver = false"
      @drop.prevent="handleDrop"
      :class="{ 'drag-over': dragOver }"
    >
      <div class="upload-content">
        <i class="upload-icon">📁</i>
        <p>目前展示的是默认数据，可拖放自定义JSON文件到这里，或</p>
        <label for="file-upload" class="browse-btn">选择文件</label>
        <input
          id="file-upload"
          type="file"
          accept=".json"
          @change="handleFileUpload"
          style="display: none"
        />
      </div>
    </div>

    <!-- 文件信息展示 -->
    <div v-if="selectedFile" class="file-info">
      <div class="file-details">
        <span class="file-name">{{ selectedFile.name }}</span>
        <span class="file-size">({{ formatFileSize(selectedFile.size) }})</span>
        <button @click="removeFile" class="remove-btn">×</button>
      </div>
      <button @click="uploadFile" :disabled="isUploading" class="upload-btn">
        {{ isUploading ? '上传中...' : '上传文件' }}
      </button>
    </div>

    <!-- 上传进度和结果反馈 -->
    <div v-if="uploadProgress > 0" class="progress-container">
      <div class="progress-bar" :style="{ width: uploadProgress + '%' }"></div>
      <span>{{ uploadProgress }}%</span>
    </div>

    <div v-if="uploadResult" class="result-message" :class="uploadResult.status">
      <p>{{ uploadResult.message }}</p>
    </div>
  </div>
</template>

<script>
import axios from 'axios'

export default {
  data() {
    return {
      dragOver: false,
      selectedFile: null,
      isUploading: false,
      uploadProgress: 0,
      uploadResult: null,
    }
  },
  methods: {
    async handleFileUpload(event) {
      this.resetState()
      const file = event.target.files[0]
      if (this.validateFile(file)) {
        this.selectedFile = file
      }
    },

    handleDrop(event) {
      this.dragOver = false
      this.resetState()
      const file = event.dataTransfer.files[0]
      if (this.validateFile(file)) {
        this.selectedFile = file
      }
    },

    validateFile(file) {
      if (!file) return false

      if (!file.name.endsWith('.json')) {
        this.uploadResult = {
          status: 'error',
          message: '请选择JSON格式的文件',
        }
        return false
      }

      if (file.size > 5 * 1024 * 1024) {
        // 2MB限制
        this.uploadResult = {
          status: 'error',
          message: '文件大小不能超过2MB',
        }
        return false
      }

      return true
    },

    formatFileSize(bytes) {
      if (bytes === 0) return '0 Bytes'
      const k = 1024
      const sizes = ['Bytes', 'KB', 'MB', 'GB']
      const i = Math.floor(Math.log(bytes) / Math.log(k))
      return parseFloat((bytes / Math.pow(k, i)).toFixed(2)) + ' ' + sizes[i]
    },

    removeFile() {
      this.selectedFile = null
      this.uploadResult = null
      this.uploadProgress = 0
      document.getElementById('file-upload').value = ''
    },

    async uploadFile() {
      if (!this.selectedFile) return

      this.isUploading = true
      this.uploadProgress = 0
      this.uploadResult = null

      const formData = new FormData()
      formData.append('file', this.selectedFile)

      try {
        const response = await axios.post('http://localhost:5000/api/upload-json', formData, {
          headers: { 'Content-Type': 'multipart/form-data' },
          onUploadProgress: (progressEvent) => {
            this.uploadProgress = Math.round((progressEvent.loaded * 100) / progressEvent.total)
          },
        })

        this.uploadResult = {
          status: 'success',
          message: '文件上传成功',
          data: response.data,
        }
      } catch (error) {
        this.uploadResult = {
          status: 'error',
          message: error.response?.data?.error || '上传失败',
          data: error.response?.data,
        }
      } finally {
        this.isUploading = false
      }
    },

    resetState() {
      this.uploadResult = null
      this.uploadProgress = 0
    },
  },
}
</script>

<style scoped>
.file-upload-container {
  max-width: 500px;
  margin: 2rem auto;
  font-family: Arial, sans-serif;
}

.drop-zone {
  border: 2px dashed #ccc;
  border-radius: 8px;
  padding: 2rem;
  text-align: center;
  cursor: pointer;
  transition: all 0.3s;
}

.drop-zone:hover,
.drag-over {
  border-color: #33131e;
  background-color: #f5f9ff;
}

.upload-content {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 0.5rem;
}

.upload-icon {
  font-size: 2.5rem;
  margin-bottom: 0.5rem;
}

.browse-btn {
  background-color: #e24a9bc2;
  color: white;
  padding: 0.5rem 1rem;
  border-radius: 4px;
  cursor: pointer;
  transition: background-color 0.3s;
}

.browse-btn:hover {
  background-color: #3a7bc8;
}

.file-info {
  margin-top: 1rem;
  padding: 1rem;
  background-color: #f5f5f5;
  border-radius: 4px;
  display: flex;
  flex-direction: column;
  gap: 1rem;
}

.file-details {
  display: flex;
  align-items: center;
  gap: 0.5rem;
}

.file-name {
  font-weight: bold;
}

.remove-btn {
  background: none;
  border: none;
  color: #23202073;
  font-size: 1.6rem;
  cursor: pointer;
  margin-left: auto;
}

.upload-btn {
  background-color: #e24a9bc2;
  color: white;
  border: none;
  padding: 0.5rem 1rem;
  border-radius: 4px;
  cursor: pointer;
  transition: background-color 0.3s;
}

.upload-btn:hover:not(:disabled) {
  background-color: #3a7bc8;
}

.upload-btn:disabled {
  background-color: #ccc;
  cursor: not-allowed;
}

.progress-container {
  margin-top: 1rem;
  background-color: #f0f0f0;
  border-radius: 4px;
  height: 24px;
  position: relative;
}

.progress-bar {
  background-color: #e24a9bc2;
  height: 100%;
  border-radius: 4px;
  transition: width 0.3s;
}

.progress-container span {
  position: absolute;
  left: 50%;
  top: 50%;
  transform: translate(-50%, -50%);
  color: #333;
  font-size: 0.8rem;
}

.result-message {
  margin-top: 1rem;
  padding: 1rem;
  border-radius: 4px;
}

.result-message.success {
  background-color: #f6ffed;
  border: 1px solid #b7eb8f;
  color: #52c41a;
}

.result-message.error {
  background-color: #fff2f0;
  border: 1px solid #ffccc7;
  color: #ff4d4f;
}

.result-message pre {
  background-color: #f5f5f5;
  padding: 0.5rem;
  border-radius: 4px;
  overflow-x: auto;
  margin-top: 0.5rem;
}
</style>
