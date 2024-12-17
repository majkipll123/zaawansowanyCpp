#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <numeric>

#include <cmath>

class thread_pool {
public:
    thread_pool(size_t thread_count)
        : stop_flag(false), total_sum(0), task_count(0) {
        for (size_t i = 0; i < thread_count; ++i) {
            workers.emplace_back(&thread_pool::worker_thread, this);
        }
    }

    ~thread_pool() {
        stop();
    }

    void add_task(std::function<double()> task) {
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            tasks.push(task);
        }
        condition.notify_one();
    }

    double average() {
        std::lock_guard<std::mutex> lock(result_mutex);
        if (task_count == 0) return 0.0; // Brak wyników
        return total_sum / static_cast<double>(task_count);
    }

    void stop() {
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            stop_flag = true;
        }
        condition.notify_all();

        for (std::thread &worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<double()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop_flag;

    std::mutex result_mutex;
    double total_sum;
    size_t task_count;

    void worker_thread() {
        while (true) {
            std::function<double()> task;
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                condition.wait(lock, [this] {
                    return stop_flag || !tasks.empty();
                });

                if (stop_flag && tasks.empty()) {
                    return;
                }

                task = std::move(tasks.front());
                tasks.pop();
            }

            double result = task();
            {
                std::lock_guard<std::mutex> lock(result_mutex);
                total_sum += result;
                ++task_count;
            }
        }
    }
};

int main() {
    thread_pool pool(4);

    // Dodaj zadania do puli
    pool.add_task([] { return std::sqrt(16.0); }); // 4.0
    pool.add_task([] { return std::sin(3.14 / 2); }); // ~1.0
    pool.add_task([] { return 42.0; }); // 42.0
    pool.add_task([] { return 1.5 * 2.0; }); // 3.0

    // Czekaj chwilę na wykonanie zadań
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Oblicz średnią wyników
    std::cout << "Average result: " << pool.average() << std::endl;

    // Zatrzymaj pulę
    pool.stop();

    return 0;
}
