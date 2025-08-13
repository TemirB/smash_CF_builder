#!/bin/bash
# nohup sh generate_and_convert.sh 16 125 = 10M events

export MC_DST=/home/tahea/McDst
export ROOTSYS=/home/tahea/root_install
export PATH=$ROOTSYS/bin:$PATH
export LD_LIBRARY_PATH=$ROOTSYS/lib:$MC_DST:$LD_LIBRARY_PATH
source $ROOTSYS/bin/thisroot.sh

# ========== Пути ==========
STORAGE="/home/tahea/smash_CF_builder/smash_CF_builder/Converter"
OSCAR_READER_DIR="/home/tahea/smash_CF_builder/smash_CF_builder/Converter"    

SMASH_BUILD_DIR="/home/tahea/smash/build"
TMP_DIR="${OSCAR_READER_DIR}/tmp"
OSCAR_DST_DIR="${OSCAR_READER_DIR}/oscarDst"
LOG_DIR="${OSCAR_READER_DIR}/data/generator/logs"

# ========== Параметры ==========
export N_TASKS=$1           # Количество ядер
export N_RUNS=$2            # Количество прогонов
export JOB_NAME=${3:-"job"} # Префикс имен

# Создаем директории
mkdir -p $TMP_DIR $OSCAR_DST_DIR $LOG_DIR

# ========== Логирование ==========
SMASH_LOG="${LOG_DIR}/${JOB_NAME}_smash.log"
CONVERT_LOG="${LOG_DIR}/${JOB_NAME}_convert.log"

# Очистка старых логов
> "$SMASH_LOG"
> "$CONVERT_LOG"

log_smash() {
    echo "[$(date +'%Y-%m-%d %H:%M:%S')] $1" >> "$SMASH_LOG"
}

log_convert() {
    echo "[$(date +'%Y-%m-%d %H:%M:%S')] $1" >> "$CONVERT_LOG"
}

# ========== Основные функции ==========
run_smash() {
    local TASK=$1
    local OUT_DIR="${TMP_DIR}/${JOB_NAME}_${TASK}"
    
    mkdir -p "$OUT_DIR"
    
    cd "$SMASH_BUILD_DIR" || exit 1
    ./smash -o "$OUT_DIR" >> "$SMASH_LOG" 2>&1
    
    if [ $? -ne 0 ]; then
        log_smash "[ERROR] генерации (Ядро $TASK) | RUN $RUN"
    fi
}

run_oscar_reader() {
    local TASK=$1
    local OUT_DIR="${TMP_DIR}/${JOB_NAME}_${TASK}"
    local OUTPUT_FILE="${OSCAR_DST_DIR}/${JOB_NAME}_${TASK}_${RUN}.McDst.root"
    
    cd "$OSCAR_READER_DIR" || exit 1
    ./converter "${OUT_DIR}/full_event_history.oscar" "$OUTPUT_FILE" >> "$CONVERT_LOG" 2>&1
    
    if [ $? -ne 0 ]; then
        log_convert "[ERROR] конвертации (Ядро $TASK) | RUN $RUN"
    fi
}

# ========== Главный цикл ==========
echo "Старт задания $JOB_NAME в $(date)" | tee -a "$SMASH_LOG" "$CONVERT_LOG"

for RUN in $(seq 1 "$N_RUNS"); do
    echo "--- RUN $RUN/$N_RUNS ---" | tee -a "$SMASH_LOG" "$CONVERT_LOG"
    
    # Параллельный запуск
    for TASK in $(seq 1 "$N_TASKS"); do
        run_smash "$TASK" &
    done
    wait
    
    for TASK in $(seq 1 "$N_TASKS"); do
        run_oscar_reader "$TASK" &
    done
    wait

    # Очистка временных файлов
    for TASK in $(seq 1 "$N_TASKS"); do
        rm -rf "${TMP_DIR}/${JOB_NAME}_${TASK}"
    done
done

echo "Завершено в $(date)" | tee -a "$SMASH_LOG" "$CONVERT_LOG"