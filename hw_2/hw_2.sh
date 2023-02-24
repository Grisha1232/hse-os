# !!! ДЗ 3 сдал ранее в эту форму
function sayHello() {
    echo "Hello"
}

function sayGoodBye() {
    echo "GoodBye"
}

function checkStatus() {
    echo "Left meeting time: $1"
}

meetingTime=10

sayHello
# Выводит оставшееся время до конца встречи
while [ $meetingTime -gt 0 ]
do
    checkStatus $meetingTime
    ((meetingTime -= 1))
    # Если время кончилось, то прощаемся
    if [ $meetingTime -eq 0 ];
    then
        sayGoodBye
    fi
done