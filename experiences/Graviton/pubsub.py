"""
Design a Pub Sub system:

Single machine / single process
Shared memory etc.


Offsets for every consumer
Can start from any offset?


Do we offload any storage to disk?
Yes?!


For later
Max number of consumers
Start pruning data?
Retention Period / TTL


Can multiple producers publish to the same topic?
Yes


Can multiple consumers consume from the same topic?
Yes!


MPMC Queue
Thread safety? Mutexes / LockFree
"""

# Topic - queue

import time

import threading
import queue

class Storage(queue.Queue):
    """In memory for now, but we can offload to disk"""
    pass


class Message():
    def __init__(self, data):
        self.cnt = 0
        self.msg = data

    def __repr__(self):
        return self.msg

class Topic():
    def __init__(self, name):
        self.name = name
        self.storage = Storage()

class Publisher(threading.Thread):

    def __init__(self, topics):
        self.topics = {t.name: t for t in topics}
        super().__init__()

    def publish(self, topic_name, msg):
        self.topics[topic_name].storage.put(msg)

    # Simulation
    def run(self):
        for i in range(5000):
            m = Message(f"Msg {i}")
            self.publish("Prices", m)
            time.sleep(1)
        

class Consumer(threading.Thread):
    def __init__(self, topic, offset=0):
        self.topic = topic
        self.start_offset = offset
        super().__init__()

    def subscribe(self):
        for _ in range(self.start_offset):
            self.topic.storage.get()

        while True:
            msg = self.topic.storage.get()
            msg.cnt += 1
            print(msg)
            if msg.cnt == 2:
                msg.task_done() # pop()
            

    def run(self):
        self.subscribe()

if __name__ == "__main__":
    t1 = Topic("Prices")
    t2 = Topic("Positions")

    p1 = Publisher([t1, t2])

    c1 = Consumer(t1, 5)
    # c2 = Consumer(t1)

    p1.start()
    c1.start()
    # c2.start()
