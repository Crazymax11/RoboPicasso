TEMPLATE = subdirs

SUBDIRS += \
    source/Core \
    source/RobopicassoApplication \
    source/Animator

RobopicassoApplication.depends = Core
Animator.depends = Core
