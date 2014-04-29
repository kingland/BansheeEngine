#pragma once

#include "CmPrerequisites.h"

namespace BansheeEngine
{
	/**
	 * @brief	These values types of notifications we would like to receive
	 *			when we start a FolderMonitor on a certain folder.
	 */
	enum class FolderChange
	{
		FileName = 0x0001, /**< Called when filename changes. */
		DirName = 0x0002, /**< Called when directory name changes. */
		Attributes = 0x0004, /**< Called when attributes changes. */
		Size = 0x0008, /**< Called when file size changes. */
		LastWrite = 0x0010, /**< Called when file is written to. */
		LastAccess = 0x0020, /**< Called when file is accessed. */
		Creation = 0x0040, /**< Called when file is created. */
		Security = 0x0080 /**< Called when file security descriptor changes. */
	};

	/**
	 * @brief	Allows you to monitor a file system folder for changes. Depending on the flags
	 *			set this monitor can notify you when file is changed/moved/renamed, etc.
	 */
	class CM_EXPORT FolderMonitor
	{
		struct Pimpl;
		class FileNotifyInfo;
		struct FolderWatchInfo;
	public:
		FolderMonitor();
		~FolderMonitor();

		/**
		 * @brief	Starts monitoring a folder at the specified path.
		 *
		 * @param	folderPath		Absolute path to the folder you want to monitor.
		 * @param	subdirectories	If true, provided folder and all of its subdirectories will be monitored
		 *							for changes. Otherwise only the provided folder will be monitored.
		 * @param	changeFilter	A set of flags you may OR together. Different notification events will
		 *							trigger depending on which flags you set.
		 */
		void startMonitor(const WString& folderPath, bool subdirectories, FolderChange changeFilter);

		/**
		 * @brief	Stops monitoring the folder at the specified path.
		 */
		void stopMonitor(const WString& folderPath);

		/**
		 * @brief	Stops monitoring all folders that are currently being monitored.
		 */
		void stopMonitorAll();

		/**
		 * @brief	Callbacks will only get fired after update is called().
		 * 			
		 * @note	Internal method.
		 */
		void _update();

		/**
		 * @brief	Triggers when a file is modified. Provides
		 *			full path to the file.
		 */
		boost::signal<void(const WString&)> onModified;

		/**
		 * @brief	Triggers when a file/folder is adeed. Provides
		 *			full path to the file/folder.
		 */
		boost::signal<void(const WString&)> onAdded;

		/**
		 * @brief	Triggers when a file/folder is removed. Provides
		 *			full path to the file/folder.
		 */
		boost::signal<void(const WString&)> onRemoved;

		/**
		 * @brief	Triggers when a file/folder is renamed. Provides
		 *			full path to the old and new name.
		 */
		boost::signal<void(const WString&, const WString&)> onRenamed;

	private:
		Pimpl* mPimpl;

		/**
		 * @brief	Worker method that monitors the IO ports for any modification notifications.
		 */
		void workerThreadMain();

		/**
		 * @brief	Called by the worker thread whenever a modification notification is received.
		 */
		void handleNotifications(FileNotifyInfo& notifyInfo, FolderWatchInfo& watchInfo);
	};
}