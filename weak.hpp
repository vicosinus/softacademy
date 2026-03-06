#ifndef WEAK_HPP
#define WEAK_HPP
#include <cstddef>
#include <utility>

namespace softacademy {

    template <typename T> class SharedPtr;

    namespace detail {
        struct ControlBlock {
            void* ptr;
            std::size_t strong_count;
            std::size_t weak_count;
            void (*deleter)(void*);

            ControlBlock(void* p, void (*d)(void*))
            : ptr(p)
            , strong_count(1)
            , weak_count(0)
            , deleter(d) {}
        };

        template <typename T>
        void default_delete(void* ptr) {
            delete static_cast<T*>(ptr);
        }
    }

    template <typename T>
    class WeakPtr {
    public:
        WeakPtr() noexcept 
        : m_ptr(nullptr) 
        , m_control(nullptr) {}

        WeakPtr(const SharedPtr<T>& sp) noexcept 
        : m_ptr(sp.m_ptr) 
        , m_control(sp.m_control) {
            inc_weak();
        }

        WeakPtr(const WeakPtr& other) noexcept 
        : m_ptr(other.m_ptr) 
        , m_control(other.m_control) {
            inc_weak();
        }

        WeakPtr(WeakPtr&& other) noexcept 
        : m_ptr(other.m_ptr) 
        , m_control(other.m_control) {
            other.m_ptr = nullptr;
            other.m_control = nullptr;
        }

        WeakPtr& operator=(const WeakPtr& other) {
            if (this != &other) {
                reset();
                m_ptr = other.m_ptr;
                m_control = other.m_control;
                inc_weak();
            }
            return *this;
        }

        WeakPtr& operator=(WeakPtr&& other) noexcept {
            if (this != &other) {
                reset();
                m_ptr = other.m_ptr;
                m_control = other.m_control;
                other.m_ptr = nullptr;
                other.m_control = nullptr;
            }
            return *this;
        }

        WeakPtr& operator=(const SharedPtr<T>& sp) noexcept {
            reset();
            m_ptr = sp.m_ptr;
            m_control = sp.m_control;
            inc_weak();
            return *this;
        }

        ~WeakPtr() {
            reset();
        }
    
    public:
        std::size_t use_count() const noexcept {
            if (m_control) {
                return m_control->strong_count;
            } else {
                return 0;
            }
        }

        bool expired() const noexcept {
            return use_count() == 0;
        }

        SharedPtr<T> lock() const noexcept {
            if (!expired()) {
                return SharedPtr<T>(*this);
            } else {
                return SharedPtr<T>();
            }
        }

        void reset() noexcept {
            dec_weak();
            m_ptr = nullptr;
            m_control = nullptr;
        }

        void swap(WeakPtr& other) noexcept {
            std::swap(m_ptr, other.m_ptr);
            std::swap(m_control, other.m_control);
        }

    private:
        T* m_ptr;
        detail::ControlBlock* m_control;

        void inc_weak() noexcept {
            if (m_control) {
                m_control->weak_count++;
            }
        }

        void dec_weak() noexcept {
            if (!m_control) {
                return;
            }

            if (m_control -> weak_count > 0) {
                m_control->weak_count--;
            }

            if (m_control->strong_count == 0 && m_control->weak_count == 0) {
                delete m_control;
                m_control = nullptr;
            }
        }

        template <typename U>
        friend class SharedPtr;
    };

}

#endif 