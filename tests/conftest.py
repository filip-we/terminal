import pytest

def pytest_addoption(parser):
    parser.addoption("--port", action="store", help="Name of serial USB connection.")

def pytest_generate_tests(metafunc):
    option_value = metafunc.config.option.port
    if 'port' in metafunc.fixturenames and option_value is not None:
        metafunc.parametrize("port", [option_value])
