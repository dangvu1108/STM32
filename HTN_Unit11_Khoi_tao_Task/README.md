# STM32 - FreeRtos
1 Mô tả bài toán

- Hệ thống sử dụng FreeRTOS Kernel để điều khiển 3 LED nhấp nháy với 3 tần số khác nhau (ví dụ 1 Hz, 2 Hz, 5 Hz).

- Mỗi LED được điều khiển bởi một task riêng biệt trong FreeRTOS, hoạt động song song (đa nhiệm giả lập) nhờ scheduler (bộ lập lịch) của hệ điều hành thời gian thực.

2 Mô tả các task

LED1_Task Bật/tắt 1 Hz = 500 ms	

LED2_Task Bật/tắt 2 Hz = 250 ms
	
LED3_Task Bật/tắt 5 Hz = 100 ms	

3 Cách hoạt động của hệ thống

3.1 Khởi tạo phần cứng:

Cấu hình 3 chân GPIO làm đầu ra cho 3 LED.

3.2 Tạo các task:

Dùng hàm xTaskCreate() để tạo 3 task, mỗi task điều khiển 1 LED.

3.3 Bắt đầu Scheduler:

Gọi vTaskStartScheduler() để FreeRTOS quản lý CPU.

Hệ thống giờ hoạt động như sau:

	- Mỗi task thực hiện bật/tắt LED, sau đó gọi vTaskDelay() để “ngủ” trong khoảng thời gian tương ứng.

	- Trong khi một task ngủ, CPU tự động chuyển sang chạy task khác → giúp các LED nhấp nháy đồng thời. 
	
4 Link video demo: https://drive.google.com/drive/folders/137O-Hfr_IiA1MYYy9XDS9_Z_3SyIJ5iu?usp=sharing