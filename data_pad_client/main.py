""" Datapad client, just read the serial and perform the actions. """
import configparser
import logging
import time

import pyautogui
import serial

config = configparser.ConfigParser()
config.read("config.cfg")

port = config["serial"]["port"]
baudrate = config["serial"]["baudrate"]
commands = config["commands_from_device"]
pyautogui_commands = config["pyautogui_commands"]

ser = serial.Serial(port, baudrate)

logger = logging.getLogger("datapad_client")
logger.setLevel(logging.DEBUG)
logger.addHandler(logging.StreamHandler())


class Locks:
    """ Make a command unavailable for a certain amount of time. """
    def __init__(self):
        self.locks = {}

    def lock(self, cmd: str, time_: int) -> None:
        """ Lock a command for a certain amount of time. """
        self.locks[cmd] = time.time() + time_

    def is_locked(self, cmd: str) -> bool:
        """ Check if a command is locked. """
        if cmd not in self.locks:
            return False
        if time.time() > self.locks[cmd]:
            del self.locks[cmd]
            return False
        return True


locks = Locks()


def decode_command(cmd: str) -> str:
    """ Decode the command from the rpi pico to a string. """
    cmd = cmd.split(" ")[0]
    if cmd not in commands:
        return None
    return commands[cmd]


def write_pyautogui_command(cmd: str) -> None:
    """ Write the pyautogui command to the screen. """
    if cmd not in pyautogui_commands:
        return
    if locks.is_locked(cmd):
        return
    pyautogui.write(pyautogui_commands[cmd])
    locks.lock(cmd, 0.2)


def decode_joystick(cmd: str) -> str:
    """ Decode the joystick command from the rpi pico to a string. """
    cmd = cmd[21:]
    x_value = int(cmd.split(" ")[0])
    y_value = int(cmd.split(" ")[1])
    return x_value, y_value


if __name__ == "__main__":
    while True:
        input_cmd = ser.readline().decode('utf-8').strip()
        decoded = decode_command(input_cmd)
        logger.debug(
            "received from device: %s, decoded to: %s", input_cmd, decoded
        )
        write_pyautogui_command(decode_command(decoded))
