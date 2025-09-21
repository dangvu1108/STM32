# STM32
UART là giao thức truyền thông nối tiếp bất đồng bộ. Nó được dùng rất nhiều trong vi điều khiển, máy tính, module ngoại vi (GPS, Bluetooth, ESP, SIM, v.v.).
1.Cấu trúc truyền dữ liệu
- Mỗi khung (frame) dữ liệu trong UART thường có dạng:
• Start bit: Luôn là 0 (mức thấp) → báo hiệu bắt đầu truyền.
• Data bits: Thông tin chính, thường là 8 bit (có thể 5, 6, 7, 9 tuỳ cấu hình).
• Parity bit: Bit kiểm tra chẵn/lẻ (Even/Odd) để phát hiện lỗi đơn giản. Có thể bật hoặc tắt.
• Stop bit: 1 hoặc 2 bit logic 1 (mức cao) → báo hiệu kết thúc khung dữ liệu.
2.Nguyên tắc hoạt động
• UART không dùng xung clock chung (khác với SPI hay I2C).
• Bên phát và bên thu phải cấu hình cùng baud rate (tốc độ truyền), ví dụ: 9600, 115200 bps.
• UART truyền dữ liệu theo dạng LSB trước, MSB sau (bit thấp trước).
• Chỉ cần 2 dây cơ bản:
o TX gửi dữ liệu.
o RX nhận dữ liệu
3.Các thông số cấu hình quan trọng
• Baud rate: tốc độ truyền (bit/giây). Ví dụ 9600, 19200, 115200 bps.
• Data bits: số bit dữ liệu (thường là 8).
• Parity: không, chẵn, hoặc lẻ.
• Stop bits: 1 hoặc 2.
• Flow control: điều khiển luồng (RTS/CTS) – thường bỏ qua trong giao tiếp đơn giản.
4.Ưu điểm
• Đơn giản, dễ dùng.
• Chỉ cần 2 dây TX/RX.
• Được tích hợp sẵn trong hầu hết vi điều khiển.
5.Nhược điểm
• Chỉ truyền point-to-point (1:1), không hỗ trợ nhiều thiết bị trên cùng bus như I2C/SPI.
• Khoảng cách hạn chế (vài mét, nếu xa phải dùng chuẩn vật lý RS232, RS485).
• Dễ sai lệch nếu 2 bên cấu hình baud rate không khớp.
