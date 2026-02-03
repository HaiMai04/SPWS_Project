# Smart Plant Watering System (SPWS) - Linux Simulation

Dự án mô phỏng **Hệ thống tưới cây tự động thông minh**, được xây dựng bằng ngôn ngữ C trên môi trường Linux. Dự án áp dụng kiến trúc phần mềm phân tầng (Layered Architecture), tách biệt giữa lớp điều khiển (Controller) và lớp phần cứng (HAL), giúp code mạch lạc và dễ mở rộng.

---

## 1. Nguyên lý Hoạt động (Operation Logic)

Hệ thống hoạt động dựa trên mô hình **Máy trạng thái (State Machine)** với vòng lặp vô hạn, thực hiện 3 bước liên tục: **Đọc Input -> Xử lý Logic -> Xuất Output**.

### A. Các chế độ hoạt động (Modes)
Hệ thống có 2 chế độ chính, chuyển đổi qua lại bằng nút nhấn:

#### 1. Chế độ Tự động (AUTO Mode) - Mặc định
Đây là chế độ giám sát thông minh không cần sự can thiệp của con người.
- **Logic kích hoạt:** Hệ thống liên tục đọc cảm biến độ ẩm đất.
    - Nếu `Độ ẩm < 50%` (Ngưỡng dưới) AND `Bơm đang tắt` => **BẬT BƠM** (LED Vàng).
    - Nếu `Độ ẩm > 80%` (Ngưỡng trên) OR `Thời gian tưới > 10s` (Bảo vệ bơm) => **TẮT BƠM** (LED Xanh).
- **Mục tiêu:** Duy trì độ ẩm đất trong khoảng lý tưởng và bảo vệ thiết bị.

#### 2. Chế độ Thủ công (MANUAL Mode)
Dành cho người dùng muốn tưới cây theo ý muốn hoặc kiểm tra thiết bị.
- **Logic:**
    - Người dùng nhấn nút kích hoạt tưới.
    - Bơm sẽ bật trong **5 giây** rồi tự động tắt.
    - Trong chế độ này, cảm biến độ ẩm chỉ dùng để hiển thị, không dùng để điều khiển bơm.

---

## 2. Mô phỏng Phần cứng (Hardware Simulation)
Vì chạy trên máy tính (PC), phần cứng được giả lập thông qua Terminal:

| Thiết bị thực tế | Mô phỏng trên Linux (HAL Layer) |
| :--- | :--- |
| **Cảm biến độ ẩm** | Sinh số ngẫu nhiên (Random) từ 40% - 80% để
