import pytest
import serial

BAUDRATE = 115200

class ExtendedSerial(serial.Serial):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

    def write_ascii(self, string):
        self.write(string.encode("ascii"))


@pytest.fixture
def con(port):
    return ExtendedSerial(
        port=port,
        baudrate=BAUDRATE,
    )

def test_hello_world(con):
    con.write("Hello, world".encode("ascii"))

def test_carrige_return(con):
    con.write_ascii("Row1")
    con.write(b'\r')
    con.write_ascii("Row2")
    con.write(b'\r')
