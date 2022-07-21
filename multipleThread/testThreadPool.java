package multipleThread;

import java.util.LinkedList;

public class testThreadPool {
    int threadPoolSize;
    LinkedList<Runnable> tasks = new LinkedList<Runnable>();

    public testThreadPool() {
        threadPoolSize = 10;
        synchronized (tasks) {
            for (int i = 0; i < threadPoolSize; i++) {
                new TaskConsumeThread("task consume thread " + i).start();
            }
        }
    }

    public void add(Runnable r) {
        synchronized (tasks) {
            tasks.add(r);
            tasks.notifyAll();
        }
    }

    class TaskConsumeThread extends Thread {
        public TaskConsumeThread(String name) {
            super(name);
        }

        Runnable task;

        @Override
        public void run() {
            while (true) {
                synchronized (tasks) {
                    while (tasks.isEmpty()) {
                        try {
                            tasks.wait();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                    task = tasks.removeLast();
                    tasks.notifyAll();
                }
                task.run();
            }
        }
    }
}
