#ifndef P20_CODE_SHAREDBOOLVAR_H
#define P20_CODE_SHAREDBOOLVAR_H

#include <condition_variable>
#include <mutex>
#include <QObject>

class SharedBoolVar : public QObject {
Q_OBJECT
public:
    SharedBoolVar(bool value) : value(value) {}

    void set(bool value) {
        std::unique_lock<std::mutex> lock(mutex);
        this->value = value;
        cv.notify_all();
        if (value) {
            emit available();
        }
    }

    bool get() {
        std::unique_lock<std::mutex> lock(mutex);
        if (value) {
            emit available();
        }
        return value;
    }

    void wait(bool target) {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this, target] { return value == target; });
        emit available();
    }

private:
    bool value;
    std::mutex mutex;
    std::condition_variable cv;

signals:

    void available();
};


#endif //P20_CODE_SHAREDBOOLVAR_H
