import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QMessageBox
from pac.hello import Ui_MainWindow
import serial.tools.list_ports
import time

class MainW(QMainWindow, Ui_MainWindow):
    bit = [0, 1, 2, 4, 8, 16, 32, 64, 128]
    a = 0
    serialFd = None

    def pflush(self):
        try:
            self.serialFd.write(bytes([0]))
        except:
            pass
        else:
            self.onStop()
        self.comboBox.clear()
        plist = list(serial.tools.list_ports.comports())
        plist = [i[0] for i in plist]
        self.comboBox.addItems(plist)

    def __init__(self):
        super(MainW, self).__init__()
        self.setupUi(self)

        self.pflush()

        self.comNum = QLabel('串口号：')
        self.statusbar.addPermanentWidget(self.comNum, stretch=0)
        self.pushButton_15.clicked.connect(self.pflush)
        self.pushButton_10.clicked.connect(self.onClose)
        self.pushButton_11.clicked.connect(self.onConnect)
        self.pushButton_12.clicked.connect(self.onStop)
        self.pushButton_2.clicked.connect(self.led2)
        self.pushButton_3.clicked.connect(self.led3)
        self.pushButton_4.clicked.connect(self.led4)
        self.pushButton_5.clicked.connect(self.led5)
        self.pushButton_6.clicked.connect(self.led6)
        self.pushButton_7.clicked.connect(self.led7)
        self.pushButton_8.clicked.connect(self.led8)
        self.pushButton_9.clicked.connect(self.runLED)
        self.pushButton_13.clicked.connect(self.read_status)
        self.pushButton_14.clicked.connect(self.light_switch)

    def erro_message(self):
        msgBox = QMessageBox()
        msgBox.setWindowTitle('错误')
        msgBox.setIcon(QMessageBox.Critical)
        msgBox.setText("串口错误,请先打开一个串口")
        msgBox.exec()

    def hello(fn):
        def wrapper(*args):
            try:
                args[0].serialFd.write(bytes([0]))
            except:
                args[0].erro_message()
            else:
                fn(args[0])
        return wrapper

    def light_switch(self):
        self.serialFd.write(b'x')
        time.sleep(0.4)
        self.serialFd.write(bytes([int(self.horizontalSlider.value())]))
        time.sleep(0.4)
        self.serialFd.write(b'x')

    def read_status(self):
        self.serialFd.write(b'r')
        z = int.from_bytes(self.serialFd.read(), 'little')
        t = 1
        res = ''
        for i in range(8):
            if z & t != 0:
                res = res + '1'
            else:
                res = res + '0'
            t <<= 1
        self.statusbar.showMessage("当前状态: "+res)


    @hello
    def onStop(self):
        self.serialFd.close()
        self.comNum.setText('串口号：')
        self.statusbar.showMessage("已断开连接")

    def onConnect(self):
        self.serialFd = serial.Serial(self.comboBox.currentText(), 9600, timeout=60)
        try:
            self.serialFd.write(bytes([0]))
        except:
            self.statusbar.showMessage("连接失败")
        else:
            self.comNum.setText("串口号：%s" % (self.comboBox.currentText()))
            self.statusbar.showMessage("连接成功")

    def onClose(self):
        self.close()

    @hello
    def led2(self):
        if self.pushButton_2.text() == "CLOSED":
            self.a |= self.bit[2]
            self.pushButton_2.setText("OPEN")
        else:
            self.pushButton_2.setText("CLOSED")
            self.a &= ~self.bit[2]
        self.serialFd.write(bytes([self.a]))

    @hello
    def led3(self):
        if self.pushButton_3.text() == "CLOSED":
            self.a |= self.bit[3]
            self.pushButton_3.setText("OPEN")
        else:
            self.pushButton_3.setText("CLOSED")
            self.a &= ~self.bit[3]
        self.serialFd.write(bytes([self.a]))

    @hello
    def led4(self):
        if self.pushButton_4.text() == "CLOSED":
            self.a |= self.bit[4]
            self.pushButton_4.setText("OPEN")
        else:
            self.pushButton_4.setText("CLOSED")
            self.a &= ~self.bit[4]
        self.serialFd.write(bytes([self.a]))

    @hello
    def led5(self):
        if self.pushButton_5.text() == "CLOSED":
            self.a |= self.bit[5]
            self.pushButton_5.setText("OPEN")
        else:
            self.pushButton_5.setText("CLOSED")
            self.a &= ~self.bit[5]
        self.serialFd.write(bytes([self.a]))

    @hello
    def led6(self):
        if self.pushButton_6.text() == "CLOSED":
            self.a |= self.bit[6]
            self.pushButton_6.setText("OPEN")
        else:
            self.pushButton_6.setText("CLOSED")
            self.a &= ~self.bit[6]
        self.serialFd.write(bytes([self.a]))

    @hello
    def led7(self):
        if self.pushButton_7.text() == "CLOSED":
            self.a |= self.bit[7]
            self.pushButton_7.setText("OPEN")
        else:
            self.pushButton_7.setText("CLOSED")
            self.a &= ~self.bit[7]
        self.serialFd.write(bytes([self.a]))

    @hello
    def led8(self):
        if self.pushButton_8.text() == "CLOSED":
            self.a |= self.bit[8]
            self.pushButton_8.setText("OPEN")
        else:
            self.pushButton_8.setText("CLOSED")
            self.a &= ~self.bit[8]
        self.serialFd.write(bytes([self.a]))

    @hello
    def runLED(self):
        t = 1
        for i in range(8):
            self.serialFd.write(bytes([t]))
            time.sleep(0.5)
            t <<= 1


if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = MainW()
    w.show()
    sys.exit(app.exec_())
