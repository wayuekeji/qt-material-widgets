When buiding custom components, 
better make components aware style, 
then components can look different when user set different style.

To achieve this, we can call `drawPrimitive()` in `paintEvent`,for example:

```c++
    QStyleOptionFocusRect option2;
    option2.initFrom(this);
    option2.backgroundColor = palette().color(QPalette::Window);

    style()->drawPrimitive(QStyle::PE_FrameFocusRect, &option2, &painter,
                          this);
```

We can custom our own style for all of our components.

reference：https://doc.qt.io/qt-6/style-reference.html