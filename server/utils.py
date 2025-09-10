#!/usr/bin/env python3
# Utils Module


import os, time


LOG_CONSOLE = "[{title}] {msg}"
LOG_FORMAT  = "{time} → [{title}] {msg}"
LOG_FILE    = time.strftime("%Y-%m-%d_%H%M%S.log")
LOGS_DIR    = ".logs"


def clear():
    os.system('cls' if os.name == 'nt' else 'clear')


def log(msg: str, title: str = 'LOG', console: bool = True):
    """Log a message to console and a log file."""

    log_msg = LOG_FORMAT
    console_msg = LOG_CONSOLE
    vars = {
        '{title}': title,
        '{msg}': msg,
        '{time}': time.strftime('%H:%M:%S'),
        '{date}': time.strftime('%Y-%m-%d'),
    }

    for k, v in vars.items():
        log_msg = log_msg.replace(k, v)
        console_msg = console_msg.replace(k, v)

    if console:
        print(console_msg)

    if not os.path.exists(LOGS_DIR):
        os.makedirs(LOGS_DIR)
    with open(os.path.join(LOGS_DIR, LOG_FILE), 'a', encoding='utf-8') as f:
        f.write(log_msg + '\n')