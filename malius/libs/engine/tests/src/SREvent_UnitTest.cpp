/*
(c) Sergey Ryazanov (http://home.onego.ru/~ryazanov)

Fast delegate compatible with C++ Standard.
*/
#ifndef SRUTIL_EVENT_INCLUDED
#define SRUTIL_EVENT_INCLUDED

namespace srutil
{
    template <typename TSink> class event_source;
    template <typename TSink> class event_binder;

    template <typename TSink> class event_binder
    {
    public:
        typedef TSink sink_type;
        typedef event_source<sink_type> event_source_type;

        event_binder() : sink(sink_type()) { next = prev = this; }
        ~event_binder() { unbind(); }

        void bind(const event_source<sink_type>& source, sink_type sink);
        void unbind()
        {
            prev->next = next;
            next->prev = prev;
            next = prev = this;
        }

    private:
        event_binder* prev;
        event_binder* next;
        sink_type sink;
        friend class event_source<sink_type>;

        void attach_after(event_binder* that)
        {
            next = that->next;
            next->prev = this;
            that->next = this;
            prev = that;
        }

        event_binder(event_binder const&);
        event_binder const& operator=(event_binder const&);
    };

    template <typename TSink> class event_source
    {
    public:
        typedef TSink sink_type;
        typedef event_binder<sink_type> binder_type;

        void bind(binder_type& bndr, sink_type sink)
        {
            bndr.attach_after(&list_head);
            bndr.sink = sink;
        }

        template <class TInvoker>
        void emit(TInvoker const& invoker)
        {
            binder_type* current = list_head.next;
            while (current != &list_head)
            {
                if (current->sink)
                {
                    event_binder<sink_type> bookmark;
                    bookmark.attach_after(current);
                    invoker(current->sink); // *current may be excluded from list, but bookmark will always keep valid
                    current = bookmark.next;
                }
                else
                    current = current->next;
            }
        }

    private:
        mutable binder_type list_head;
        friend class event_binder<sink_type>;
    };

    template <typename TSink>
    void event_binder<TSink>::bind(const event_source<sink_type>& source, sink_type sink)
    {
        unbind();

        attach_after(&source.list_head);
        this->sink = sink;
    }
}
#endif// SRUTIL_EVENT_INCLUDED

/*
An example of using SRUtil.Event library with callback interfaces.


*/
#include <iostream>

class Widget
{
public:
    class MouseEventsListener;
    typedef srutil::event_source<MouseEventsListener*> MouseEventsSource;

    MouseEventsSource const & getMouseEventsSource() const { return mouseEventSource; }
    void Test();

private:
    MouseEventsSource mouseEventSource;
};

class Widget::MouseEventsListener
{
public:
    virtual void onMouseMove(int x, int y) = 0;
    virtual void onMouseDown(int x, int y, int button) = 0;
    virtual void onMouseUp(int x, int y, int button) = 0;
};

class WidgetObserver : Widget::MouseEventsListener
{
public:
    WidgetObserver(Widget* widget)
    {
        binder.bind(widget->getMouseEventsSource(), this);
    }

private:
    // event_binder<MouseEventsListener*>
    Widget::MouseEventsSource::binder_type binder;

    void onMouseMove(int x, int y) { std::cout << "Mouse pointer moved to (" << x << ", " << y << ").\n"; }
    void onMouseDown(int x, int y, int button) { std::cout << "Mouse button " << button << " pressed at (" << x << ", " << y << ").\n"; }
    void onMouseUp(int x, int y, int button) { std::cout << "Mouse button " << button << " released at (" << x << ", " << y << ").\n"; }
};

void Widget::Test()
{
    //mouseEventSource.emit(boost::bind(&MouseEventsListener::onMouseDown, _1, 10, 10, 1));
    //mouseEventSource.emit(boost::bind(&MouseEventsListener::onMouseMove, _1, 15, 15));
    //mouseEventSource.emit(boost::bind(&MouseEventsListener::onMouseMove, _1, 20, 15));
    //mouseEventSource.emit(boost::bind(&MouseEventsListener::onMouseMove, _1, 25, 15));
    //mouseEventSource.emit(boost::bind(&MouseEventsListener::onMouseMove, _1, 25, 20));
    //mouseEventSource.emit(boost::bind(&MouseEventsListener::onMouseUp, _1, 25, 20, 1));
}

int main()
{
    Widget widget;
    widget.Test(); // no listeners, nothing happened

    WidgetObserver observer(&widget);
    widget.Test(); // observer revieves events

    return 0;
}
