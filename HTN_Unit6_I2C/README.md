# STM32
1. Khái niệm
• I²C = Inter-Integrated Circuit
• Là giao thức truyền thông nối tiếp, do Philips (nay là NXP) phát triển.
• Đặc điểm:
 Dây:
 SCL (Serial Clock) – xung clock do Master tạo ra.
 SDA (Serial Data) – đường dữ liệu (song công nửa – half-duplex).
o Hỗ trợ nhiều thiết bị (multi-master, multi-slave).
o Tốc độ chuẩn:
 Standard mode: 100 kHz
 Fast mode: 400 kHz
 Fast mode plus: 1 MHz
 High speed: 3.4 MHz

2. Cấu trúc bus
• Master: tạo tín hiệu clock, khởi tạo giao tiếp.
• Slave: thiết bị được master hỏi hoặc điều khiển (ví dụ cảm biến).
• Mỗi slave có một địa chỉ 7-bit hoặc 10-bit duy nhất trên bus.

3. Tín hiệu cơ bản
3.1. START (S):
o Master kéo SDA từ High → Low trong khi SCL đang High.
o Báo hiệu bắt đầu một phiên giao tiếp.
3.2. STOP (P):
o Master kéo SDA từ Low → High trong khi SCL đang High.
o Báo hiệu kết thúc giao tiếp.
3.3. Data bit:
o Truyền từng bit trên SDA, được đồng bộ bởi xung SCL.
o Dữ liệu chỉ thay đổi khi SCL = Low, và được chốt (sample) khi SCL = High.
3.4. ACK / NACK:
o Sau mỗi byte (8 bit), bên nhận phải trả về ACK (0) nếu nhận thành công.
o Nếu không muốn nhận thêm dữ liệu → gửi NACK (1).

4. Trình tự giao tiếp I²C
Ví dụ master gửi dữ liệu cho slave:
4.1. START condition
4.2. Địa chỉ slave (7-bit) + bit R/W
o R/W = 0 → master ghi vào slave
o R/W = 1 → master đọc từ slave
o Slave có địa chỉ đúng sẽ ACK.
4.3. Dữ liệu (8 bit)
o Master gửi 1 byte dữ liệu.
o Slave trả ACK.
o Có thể gửi nhiều byte liên tiếp.
4.4. STOP condition
o Master gửi STOP để kết thúc.

