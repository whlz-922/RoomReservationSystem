# RoomReservationSystem
机房管理系统：基于c++面向对象的特性，实现从登录到用户操作，再到注销的功能。
语言基础构成：c++; STL（string，vector，map）; fstream文件操作等。
代码阅读顺序：main.cpp -> identity.h（父类，利用面向对象的继承和多态特性封装用户身份信息） -> manager.h/manager.cpp（管理员类，用以管理平台账号） 
            -> globalFile.h（存储账号信息，预约信息等）->student.h/student.cpp（学生类，可进行机房预约）->orderFile.h/orderFile.cpp（更新预约的信息）
            -> teacher.h/teacher.cpp（教师类，用以审核学生提交的预约）
