import pytest
import serial

BAUDRATE = 115200

@pytest.fixture
def con(port):
    return serial.Serial(
        port=port,
        baudrate=BAUDRATE,
    )

def test_hello_world(con):
    con.write("Hello, world".encode("ascii"))
