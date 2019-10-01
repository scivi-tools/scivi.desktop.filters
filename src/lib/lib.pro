TEMPLATE = subdirs

SUBDIRS += \
    Constant \
    Console \
    LinearDatetime \
    Scene \
    Color \
    InputFile \
    AreaDatetime \
    VerticalStack \
    HorizontalStack \
    GridInputFile \
    SmoothSurface \
    Surface3D \
    BaseWebSocketInput \
    WebSocketInput \
    CursorActuator \
    TimeSeriesAdapter \
    FloatAdapter \
    Gauge \
    Mouse \
    Glove \
    Orientation2Coord \

WebSocketInput.depends = BaseWebSocketInput
