#pkg install inotify-tools
#sudo apt -y install inotify-tools
while true; do 
  inotifywait -qm --event modify --format '%w' ./*.c ./*.h | (./build.sh && ./run.sh)
done
