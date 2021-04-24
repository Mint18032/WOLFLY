WOLFLY
Hướng dẫn cài đặt
1. Cài đặt:
- Chương trình sử dụng file project của Code::Blocks.
- Hãy chắc chắn rằng bạn đã tải đầy đủ Code::Blocks, Mingw và các thư viện SDL2, SDL_image, SDL_ttf, SDL_mixer bản tương thích với thiết bị được sử dụng.
- Tải thư mục WOLFLY và một trong 2 tệp trong thư mục SDL nếu chưa có: Trên Github https://github.com/Mint18032/WOLFLY trong mục "Code" màu xanh lá, chọn "Download zip".
- Sửa lại đường dẫn vào file SDL:
	+ Nếu bạn chưa có sẵn các thư viện liên kết (các file .dll) trong System, hãy lấy chúng từ SDL2/bin và thả vào thư mục WOLFLY hoặc System32 (với máy 32 bit)/SysWOW64 (với máy 64 bit).
	+ Mở WOLFLY.cbp bằng Code::Blocks, trong Project/Build options/Search directories/Compiler xóa đường dẫn cũ và thay bằng đường dẫn tới thư mục include/SDL2.
					   trong Linkers xóa đường dẫn cũ và thay bằng đường dẫn tới thư mục lib ứng với các thư viện trên.
2. Chạy chương trình:
- Chọn Build/Rebuild trên thanh điều khiển (hoặc ấn Ctrl-F11), nếu không thành công hãy thử khởi động lại Code::Blocks hoặc kiểm tra lại các thao tác.
- Sau khi build thành công thì chương trình có thể chạy.

*Lưu ý: - Các tệp, thư mục nằm trong tệp WOLFLY bắt buộc phải có và không được thay đổi để chương trình không phát sinh lỗi khi chạy. Chức năng cụ thể đã được chú thích trong từng tệp.
	- Các đường dẫn cần thiết nằm trong README.md (https://github.com/Mint18032/WOLFLY/blob/main/README.md).

Các chức năng chính
1. Màn hình Menu: 
- Hai nút điều khiển nhạc nền và âm thanh (bao gồm tắt/bật toàn bộ hiệu ứng âm thanh và nhạc nền) được tách riêng thuận tiện hơn cho nhu cầu của người chơi.
- Kỉ lục cao nhất được ghi trên góc phải màn hình.
- Có 2 cách tắt chương trình: sử dụng nút tắt ở cửa sổ hoặc nút tắt góc trái Menu.
- Bắt đầu vào game bằng ấn nút Play hoặc phím cách trên bàn phím.
2. Trước khi vào game sẽ có màn hình hướng dẫn chơi, cụ thể:
- Sử dụng các phím: lên, xuống, trái, phải trên bàn phím để di chuyển chú sói.
- Ăn cừu để tăng điểm.
- Chú sói sẽ chết khi chạm vào sao rơi.
3. Màn hình chơi:
- Các nhân vật:
	+ Chú sói màu xám, có thể quay đầu 2 bên, đổi màu theo màu cừu ăn được, khi ăn có thể mở miệng và kèm theo hiệu ứng âm thanh.
	+ Các ngôi sao rơi với âm thanh mỗi khi xuất hiện, sao xuất hiện nhiều dần và tối đa 4 ngôi sao một lúc.
	+ Cừu gồm 7 màu, mỗi lần đi ra khỏi màn hình mà không bị sói ăn sẽ có tiếng kêu.
- Nút Play diễn tả trạng thái chơi hay dừng game ở góc phải màn hình.
- Số điểm đang có và số điểm cao nhất ở góc trái màn hình.
4. Màn hình tạm dừng game:
- Xuất hiện khi ấn nút Play trên góc trái màn hình hoặc ấn phím cách trong quá trình chơi.
- Có thể thực hiện 3 thao tác:
	+ Ấn nút Menu hoặc dấu X để trở lại Menu.
	+ Ấn nút Pause trên góc trái màn hình hoặc nút Continue ở giữa hoặc 1 phím bất kì trên bàn phím để tiếp tục chơi.
	+ Ấn nút Replay để chơi lại ván mới.
5. Màn hình kết thúc game:
- Xuất hiện khi sói đã va phải sao và chết.
- Hiển thị số điểm và thông báo "New high score" nếu có kỉ lục mới.
- Có thể thực hiện 2 thao tác:
	+ Ấn nút Menu hoặc dấu X để trở lại Menu.
	+ Ấn nút Replay để chơi lại ván mới.
6. Chức năng khác:
- Thu phóng màn hình: màn hình có thể thu phóng nhưng luôn theo tỉ lệ 17:10, ấn phím ESC trên bàn phím để trở lại kích cỡ mặc định.
- Lưu kỉ lục: tự động tạo file lưu kỉ lục trong lần đầu chạy chương trình và lưu kỉ lục đó đến khi đạt kỉ lục cao hơn.

---------------------------------------------------------------------------------------------------------------------------------------
(English)

Setting
- The program uses the project file of Code::Blocks.
- Make sure you have fully downloaded Code::Blocks, Mingw, and SDL2, SDL_image, SDL_ttf, SDL_mixer libraries compatible with the device.
- Download the WOLFLY folder and one of the 2 files in the SDL folder if your device does not have one: On Github https://github.com/Mint18032/WOLFLY click the green "Code" button, select "Download zip".
- Modify the path to the SDL file:
	+ If you do not have the dinamic linked library files of SDL (.dll files) in your Computer's System, get them from SDL2/bin and move them to WOLFLY or System32 (for 32 bit)/SysWOW64 (for 64 bit).
	+ Open WOLFLY.cbp with Code::Blocks, in Project/Build options/Search directories/Compiler delete the old path and replace it with the path to the directory include/SDL2.
					     in Linkers delete the old path and replace it with the path to the lib directory corresponding to the above libraries.

Run
- You have to build the project before running it. Check your operations or restart Code::Blocks if build failed.
- After having successfully built, the program should run properly.

* Note: - The files and folders in the WOLFLY folder are required and must not be changed so that the program does not generate errors when running. Specific functionalities of these file have been annotated inside.
	- Some necessary paths are written in README.md (https://github.com/Mint18032/WOLFLY/blob/main/README.md).

Main functions
1. Menu screen:
- Two buttons: background music controller and sound controller (including all sound effects and background music) are separated.
- The highest score is rendered in the right corner of the screen.
- There are two ways to turn off the program: use the X button in the window or the Quit button in the left corner of the Menu.
- Start game by pressing the Play button or the spacebar on the keyboard.
2. Before entering the game, there will be a screen to let you know the guide of the game, including:
- Use the keys: up, down, left, right on the keyboard to move the wolf.
- Eat sheep to gain points.
- The wolf will die when it touches the falling stars.
3. Play screen:
- The characters:
	+ The wolf is gray at the beginning and can turn its head left/right, changes color according to the color of the eaten sheep, opens its mouth when eating.
	+ The stars are alway appear with sound effects. There will be more and more stars and up to 4 stars can appear at the same time.
	+ Sheep include 7 colors, each time one of them go out of the screen without being eaten, it will bleat.
- A play button, which describes the status of playing or stopping the game, is displayed in the right corner of the screen.
- Number of points gained and best score are displayed in the left corner of the screen.
4. Pause screen:
- Appears when clicking the Play button on the left corner of the screen or pressing the spacebar while playing.
- You can perform 3 actions:
	+ Click Menu button or X lable to return to Menu.
	+ Click the Pause button on the left corner of the screen or the Continue button in the middle or press any key on the keyboard to continue playing.
	+ Click the Replay button to start again.
5. End game screen:
- Appears when a wolf collided with a star and dies.
- Display score and notice "New high score" if there is a new record.
- Can perform 2 actions:
	+ Click Menu button or X lable to return to Menu.
	+ Click the Replay button to start again.
6. Other functions:
- Zoom program's window: the window can be zoomed in/zoomed out/maximized/minimized but always in the 17:10 aspect ratio. Press ESC key to turn to default size.
- Save record: Automatically create a record-saving file in the first time you run the program and save that record until you reach a higher score.
