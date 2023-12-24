#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#define INDEX_HTML "interface/index.html"

#include <vector>
#include <stdlib.h>

namespace net
{
    namespace interface 
    {
        class user
        {
        public:
            class userCredentials
            {
            private:
                char *username, *password;
                int id;
            public:
                userCredentials(const char *username, const char *password, const int id);

                char *getUsername(void) const noexcept;
                char *getPassword(void) const noexcept;
                int getId(void) const noexcept;

                ~userCredentials() = default;
            };

        public:
            class userFiles
            {
            private:
                char *fileName;
                int id, fileSize, noDownloads;

            public:
                userFiles(const char *fileName, const int id, const int fileSize, const int noDownloads);

                char *getFileName(void) const noexcept;
                long long unsigned int getId(void) const noexcept;
                int getFileSize(void) const noexcept;
                int getNoDownloads(void) const noexcept;

                ~userFiles() = default;
            };

        private:
            int SESSION_ID;
            std::vector<user::userCredentials> uc;  // log in user credentials
            std::vector<user::userFiles>       uf;  // user files by SESSION ID
            
        public:
            user();

            std::vector<class userCredentials> getUserCredentials(void) const noexcept;
            std::vector<class userFiles> getUserFiles(void) const noexcept;
            int getSessionID(void) const noexcept;

            void clearUserCredentials(void) noexcept;
            void clearUserFiles(void) noexcept;

            int loginRoute(char *request, int acceptedSocketFileDescriptor);
            int addFilesRoute(const char *buffer, int acceptedSocketFileDescriptor, ssize_t __bytesReceived);

            void addToUserCredentials(const userCredentials __uc) noexcept;
            void addToUserFiles(const userFiles __uf) noexcept;

            bool validateCredentials(char *username, char *password);

            void buildIndexHTML(void);

            ~user() = default;
        };
    }
}

#endif