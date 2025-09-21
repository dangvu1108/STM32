# STM32
1. SPI là một giao thức giao tiếp phổ biến được sử dụng bởi nhiều thiết bị khác nhau. Ví dụ, module thẻ SD, module đầu đọc thẻ RFID và bộ phát / thu không dây 2,4 GHz đều sử dụng SPI để giao tiếp với vi điều khiển.

Lợi ích duy nhất của SPI là dữ liệu có thể được truyền mà không bị gián đoạn. Bất kỳ số lượng bit nào cũng có thể được gửi hoặc nhận trong một luồng liên tục. Với I2C và UART, dữ liệu được gửi dưới dạng gói, giới hạn ở một số bit cụ thể. Điều kiện bắt đầu và dừng xác định điểm bắt đầu và kết thúc của mỗi gói, do đó dữ liệu bị gián đoạn trong quá trình truyền.

Các thiết bị giao tiếp qua SPI có quan hệ master - slave. Master là thiết bị điều khiển (thường là vi điều khiển), còn slave (thường là cảm biến, màn hình hoặc chip nhớ) nhận lệnh từ master. Cấu hình đơn giản nhất của SPI là hệ thống một slave, một master duy nhất, nhưng một master có thể điều khiển nhiều hơn một slave.

MOSI (đầu ra master / đầu vào slave) - đường truyền cho master gửi dữ liệu đến slave.

MISO (đầu vào master / đầu ra slave) - đường cho slave gửi dữ liệu đến master.

SCLK (clock) - đường cho tín hiệu xung nhịp.

SS / CS (Slave Select / Chip Select) - đường cho master chọn slave nào để gửi tín hiệu.

2. Cách hoạt động cuả SPI

Xung nhịp

Tín hiệu xung nhịp đồng bộ hóa đầu ra của các bit dữ liệu từ master để lấy mẫu các bit của slave. Một bit dữ liệu được truyền trong mỗi chu kỳ xung nhịp, do đó tốc độ truyền dữ liệu được xác định bởi tần số của tín hiệu xung nhịp. Giao tiếp SPI được khởi tạo bởi master kể từ khi master cấu hình và tạo ra tín hiệu xung nhịp.

Bất kỳ giao thức giao tiếp nào mà các thiết bị chia sẻ tín hiệu xung nhịp thì đều được gọi là đồng bộ. SPI là một giao thức giao tiếp đồng bộ. Ngoài ra còn có các phương thức không đồng bộ không sử dụng tín hiệu xung nhịp. Ví dụ, trong giao tiếp UART, cả hai bên đều được đặt thành tốc độ truyền được cấu hình sẵn để chỉ ra tốc độ và thời gian truyền dữ liệu.

Tín hiệu xung nhịp trong SPI có thể được sửa bằng cách sử dụng các thuộc tính của phân cực xung nhịp và pha xung nhịp. Hai thuộc tính này làm việc cùng nhau để xác định khi nào các bit được xuất ra và khi được lấy mẫu. Phân cực xung nhịp có thể được thiết lập bởi master để cho phép các bit được xuất ra và lấy mẫu trên cạnh lên hoặc xuống của chu kỳ xung nhịp. Pha xung nhịp có thể được đặt để đầu ra và lấy mẫu xảy ra trên cạnh đầu tiên hoặc cạnh thứ hai của chu kỳ xung nhịp, bất kể nó đang tăng hay giảm.

Slave Select

Master có thể chọn slave mà nó muốn giao tiếp bằng cách đặt đường CS / SS của slave ở mức điện áp thấp. Ở trạng thái idle, không truyền tải, dòng slave select được giữ ở mức điện áp cao. Nhiều chân CS / SS có thể có sẵn trên thiết bị master cho phép đấu dây song song nhiều slave. Nếu chỉ có một chân CS / SS, nhiều slave có thể được kết nối với master bằng cách nối chuỗi.

MOSI và MISO

Master gửi dữ liệu đến slave từng bit, nối tiếp qua đường MOSI. Slave nhận dữ liệu được gửi từ master tại chân MOSI. Dữ liệu được gửi từ master đến slave thường được gửi với bit quan trọng nhất trước.

Slave cũng có thể gửi dữ liệu trở lại master thông qua đường MISO nối tiếp. Dữ liệu được gửi từ slave trở lại master thường được gửi với bit ít quan trọng nhất trước.

3. Các bước truyền dữ liệu SPI

Master ra tín hiệu xung nhịp.
 
Master chuyển chân SS / CS sang trạng thái điện áp thấp, điều này sẽ kích hoạt slave.
 
Master gửi dữ liệu từng bit một tới slave dọc theo đường MOSI. Slave đọc các bit khi nó nhận được.
 
Nếu cần phản hồi, slave sẽ trả lại dữ liệu từng bit một cho master dọc theo đường MISO. Master đọc các bit khi nó nhận được.
 
4. Ưu và nhược điểm của SPI

Có một số ưu và nhược điểm khi sử dụng SPI và nếu được lựa chọn giữa các giao thức giao tiếp khác nhau, bạn nên biết khi nào sử dụng SPI theo yêu cầu của dự án:

4.1. Ưu điểm

Không có bit bắt đầu và dừng, vì vậy dữ liệu có thể được truyền liên tục mà không bị gián đoạn

Không có hệ thống định địa chỉ slave phức tạp như I2C

Tốc độ truyền dữ liệu cao hơn I2C (nhanh gần gấp đôi)

Các đường MISO và MOSI riêng biệt, vì vậy dữ liệu có thể được gửi và nhận cùng một lúc

4.2. Nhược điểm

Sử dụng bốn dây (I2C và UART sử dụng hai)

Không xác nhận dữ liệu đã được nhận thành công (I2C có điều này)

Không có hình thức kiểm tra lỗi như bit chẵn lẻ trong UART

Chỉ cho phép một master duy nhất