# PowerGauge-Challenge1
QT QML - Dynamic QObject and QML Component Creation

## Environment
- Windows 10/11 Qt Creator
- Kit1: Desktop Qt 6.8.1 MSVC2022 64bit
- Kit2: Desktop Qt 6.8.1 MinGW 64bit
## Build Steps
- Open CMakeLists.txt as project in Qt creator
- Select Kit1(Desktop Qt 6.8.1 MSVC2022 64bit) or Kit2(Desktop Qt 6.8.1 MinGW 64bit)
- Build and Run in Debug or Release mode
  
![Challenge1](https://github.com/user-attachments/assets/c9f02e31-a3d6-46f1-b00f-89841f721633)
## Project architecture
- CMakeLists.txt
  - Qt Quick(QML) Project file
  - REQUIRES: >= Cmake 3.16, >= Qt6.5, C++17
- Backend Files
  - Backend Class
    - Backend Qt/C++ Singletone Class
      - It can be accessed as "Backend" on qml
        ```
        QQmlContext *context = engine.rootContext();
        context->setContextProperty("Backend", Backend::instance());
        ```
      - Read configuration json file
      - Parse json content to array(dataList property) for create instances of QML Rectangles on main window.
        ```
        Q_PROPERTY(QVariantList dataList READ dataList NOTIFY dataListChanged)
        ```
      - Create objects of DataRect QML component by QML Instantiator
        ```
        property var mDataList: Backend ? Backend.dataList : []

        Instantiator {
            model: mDataList

            delegate: DataRect {
                rectData: modelData
                ...
            }
        }
        ```
  - DataSource Class
    - Data from such an object should be used to instantiate an object of a QObject. \
      It is each of object for result of parsing dataSource*.json
      It can be used as "DataSource" by qmlRegisterType.
      ```
      qmlRegisterType<DataSource>("Challenge", 1, 0, "DataSource");
      ```
    - When active property is true, its starttimer is called and make sure its val property is updated between min and max per msec seconds
      ```
      void DataSource::updateVal()
      {
          m_val = QRandomGenerator::global()->bounded(m_min, m_max);
          emit valChanged(m_val);
          qDebug() << QString("%1 value changed to %2").arg(m_id).arg(m_val);
      }
      
      void DataSource::setActive(bool newActive)
      {
          if (m_active != newActive) {
              m_active = newActive;
      
              if (m_timerId > 0) {
                  killTimer(m_timerId);
                  m_timerId = -1;
              }
      
              if (newActive) {
                  m_timerId = startTimer(m_msec);
              }
      
              emit activeChanged(newActive);
          }
      }
      
      int DataSource::val() const
      {
          return m_val;
      }
      
      void DataSource::timerEvent(QTimerEvent *event)
      {
          int timerId = event->timerId();
          if (m_timerId == timerId) {
              updateVal();
          }
      }
      ```
- UI Files
  - main.qml \
    MainWindow UI File \
    Create objects of DataRect QML component by QML Instantiator with Backend.dataList
    ```
    Instantiator {
          model: mDataList

          delegate: DataRect {
              rectData: modelData
              parent: recContent
              ...
          }
      }
    ```
  - DataRect.qml \
    Custom QML Rectangle(moving horizontally) Component UI File \
    ModelData is each object of array Backend.dataList \
    dataSource property of each ModelData is just DataSource class \
    Text in DataReact shows DataSource.val \
    Text is changed to "XXXXXX" and stops updating Val of DataSource When DataReact is in the right half of the window
    ```
    property var rectData: modelData
    property DataSource dataSource: rectData.dataSource

    property bool shouldBeUpdate: dataRect.x + dataRect.width < parentWidth / 2
    onShouldBeUpdateChanged: {
        if (dataSource) {
            dataSource.active = dataRect.shouldBeUpdate
        }
    }

    Text {
        id: txtValue
        anchors.centerIn: parent
        font.pointSize: 12
        color: "#ffffff"
        text: dataSource && dataSource.active ?
                  qsTr("%1: %2").arg(dataId).arg(dataSource.val) :
                  qsTr("XXXXX")
    }
    ```
- Configuration Files
  - example of 1 instance: dataSource1.json, dataList1.json
  - example of 3 instance: dataSource3.json, dataList3.json
  - example of 5 instance: dataSource5.json, dataList5.json
  - How to Change configuration files when app is started
    ```
    // line 3-4 backend.cpp
    // Change FILE_DATALIST and FILE_DATASOURCE
    
    #include "backend.h"

    #define FILE_DATALIST "dataList5.json"
    #define FILE_DATASOURCE "dataSource5.json"
    ```
