#!/bin/bash

# Настройка переменных окружения
export MC_DST=/home/tahea/McDst
export OSCAR_INPUT_DIR=/home/tahea/smash/build/data/8

# Проверка существования директорий
if [ ! -d "$MC_DST" ]; then
  echo "[WARNING]: MC_DST '$MC_DST' does not exist."
fi
if [ ! -d "$OSCAR_INPUT_DIR" ]; then
  echo "[WARNING]: OSCAR_INPUT_DIR '$OSCAR_INPUT_DIR' does not exist."
fi

# Для динамической библиотеки, добавляем libMcDst.so в LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$MC_DST:$LD_LIBRARY_PATH

echo "Environment variables have been set:"
echo "  MC_DST=$MC_DST"
echo "  OSCAR_INPUT_DIR=$OSCAR_INPUT_DIR"
echo "  LD_LIBRARY_PATH=$LD_LIBRARY_PATH"

# Сборка проекта
echo "Running make clean && make..."
make clean && make
