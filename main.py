from kivy.app import App
from kivy.uix.widget import Widget
from kivy.graphics import Rectangle, Color
from kivy.uix.button import Button
from kivy.uix.label import Label
from kivy.clock import Clock
import serial
import time

#define status
status='unknown'

serialport = serial.Serial(
    port='/dev/ttyACM0',
    baudrate = 9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS)

class Interface(Widget):
    def __init__(self, **kwargs):
        super(Interface, self).__init__(**kwargs)
        with self.canvas:
            self.rect = Rectangle(pos=self.pos, size=self.size)
            # add your instruction for main canvas here

class StopApp(App):
    def build(self):
        parent=Interface()

        #Create Stop button
        stopbtn = Button(text='Stop',background_color=(1.0, 0.0, 0.0, 1.0),pos=(parent.right,0))
        stopbtn.bind(on_press=self.send_stop)
        parent.add_widget(stopbtn)

        #Create Start button
        startbtn = Button(text='Start',background_color=(0.0, 1.0, 0.0, 1.0))
        startbtn.bind(on_press=self.send_start)
        parent.add_widget(startbtn)   

        #Display Time of Day Clock
        timeofday = clockupdate(pos=(parent.center_x,200))
        Clock.schedule_interval(timeofday.update, 1)
        parent.add_widget(timeofday)
        
        enginestatus =readstatus(pos=(parent.center_x,175))
        Clock.schedule_interval(enginestatus.check, 1)
        parent.add_widget(enginestatus)

        return parent
    def send_stop(self, obj):
        print('Stop')
        global status
        status='Engine stopped'
        serialport.write('stop')

    def send_start(self, obj):
        print('Start')
        global status
        status=('Engine Running')


class readstatus(Label):
    def check(self, *args):
        self.text=serialport.readline()

class clockupdate(Label):
    def update(self, *args):
        self.text = time.asctime()
        





if __name__ == '__main__':
    StopApp().run()
