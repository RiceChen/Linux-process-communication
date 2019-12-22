<div align="center">
    <h1>
        《消息队列（Message queue)》
    </h1>
</div>

<h2>Message queue概述 </h2>
<ul>
    <h3>
        <li>消息队列是IPC对象的一种</li>
        <li>消息队列有消息队列ID来唯一标识</li>
        <li>消息队列就是一个消息的列别。用户可以在消息队列中添加消息、读取消息</li>
        <li>消息队列可以按照类型来发送/接受消息</li>
    </h3>
    <h3>消息队列的操作</h3>
    <h4>
        <li>创建消息队列</li>
        <li>添加消息</li>
        <li>读取消息</li>
        <li>控制消息队列</li>
    </h4>
</ul>

<h2>消息队列相关函数</h2>
<ul>
    <h3>
        <li>msgget()函数：创建或打开消息队列，这里穿件的消息队列的数量会受到系统消息队列数量的限制</li>
            <div align="center">
                <img src="../picture/message_queue_msgget_func.png" width="70%">
            </div>
        <li>msgsnd()函数：发送消息，按照类型把消息添加到已打开的消息队列末尾</li>
            <div align="center">
                <img src="../picture/message_queue_msgsnd_func.png" width="70%">
            </div>
        <li>msgrcv()函数：读取消息，按照类型把消息从消息队列中取走</li>
            <div align="center">
                <img src="../picture/message_queue_msgrcv_func.png" width="70%">
            </div>
        <li>msgctl()函数：控制消息队列</li>
            <div align="center">
                <img src="../picture/message_queue_msgctl_func.png" width="70%">
            </div>
    </h3>
</ul>