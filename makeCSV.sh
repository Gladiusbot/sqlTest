#!/bin/bash

start_time=$(date +%s)

for((i=1; i<=10; i++)); do
    file_name="data_${i}.csv"
    python3 makeCSV.py "csvFiles/$file_name" &
done

wait

end_time=$(date +%s)

elapsed_time=$((end_time - start_time))

echo "makeCSV.sh脚本执行时间: $elapsed_time 秒"