TEMPLATE = subdirs

SUBDIRS += \
    source/Core \
    source/RobopicassoApplication \
    source/Animator \
    source/JsonViewer

RobopicassoApplication.depends = Core
Animator.depends = Core
JsonViewer.depends = Core
