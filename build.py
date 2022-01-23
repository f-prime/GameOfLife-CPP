#!/usr/bin/python3

import os
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("-r", action="store_true")
args = parser.parse_args()

CC = "g++-11"
FLAGS = "-Llib/raylib -lraylib -std=c++20"
OUTPUT = "game_of_life"
files = " ".join([os.path.join(folder, file) for folder, _, files in os.walk("src") for file in files if file.endswith(".cpp")])
compile_command = f"{CC} {FLAGS} {files} -o {OUTPUT}"
result = os.system(compile_command)

if args.r and result == 0:
    os.system(f"./{OUTPUT}")
