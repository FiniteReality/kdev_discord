cmake_minimum_required(VERSION 2.8.12)

add_subdirectory(thirdparty/discord-rpc)

project(kdev_discord)

include_directories(thirdparty/discord-rpc/include)

find_package(ECM "5.14.0" REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMQtDeclareLoggingCategory)
include(FeatureSummary)

find_package(KDevPlatform 5.1.40 REQUIRED)
find_package(KF5TextEditor)

add_subdirectory(src)

# kdebugsettings file
install(FILES kdev_discord.categories DESTINATION ${KDE_INSTALL_CONFDIR})

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
