# Пакет Basic feature / Basic feature package

Пакет демонстрирует базовые возможности Robot Operation System (ROS), т.е. service, publisher и subscriber, 
на примере адаптации игры "Стеклянный мост" из сериала "Игра в кальмара" ("Glass Bridge" from "Squid Game").
Узел осуществляет проверку запроса пользователя (0 или 1) и возвращает в ответном сообщении текущее положение ("move next" или "dead").

## Процедура запуска / Launch

Запуск узла с параметрами по умолчанию:
```lang-bash
  roslaunch basic_feature game.launch
```
Запрос к узлу:
```lang-bash
  rosservice call /check_step "step: 0"
```

## Примеры работы / Examples

![](https://github.com/TonyCooT/basic_feature/blob/main/images/example.jpg)
