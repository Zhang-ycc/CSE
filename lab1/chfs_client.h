#ifndef chfs_client_h
#define chfs_client_h

#include <string>
//#include "chfs_protocol.h"
#include "extent_client.h"
#include <vector>

using namespace std;


class chfs_client {
  extent_client *ec;
 public:

  typedef unsigned long long inum;
  enum xxstatus { OK, RPCERR, NOENT, IOERR, EXIST };
  typedef int status;

  struct fileinfo {
    unsigned long long size;
    unsigned long atime;
    unsigned long mtime;
    unsigned long ctime;
  };
  struct dirinfo {
    unsigned long atime;
    unsigned long mtime;
    unsigned long ctime;
  };
  struct dirent {
    std::string name;
    chfs_client::inum inum;
  };

  struct symlinkinfo {
      unsigned long long size;
      unsigned long atime;
      unsigned long mtime;
      unsigned long ctime;
  };


 private:
  static std::string filename(inum);
  static inum n2i(std::string);
    static string i2n(inum);
    static string entry(const char *, inum);

 public:
  chfs_client();
  chfs_client(std::string, std::string);

  bool isfile(inum);
  bool isdir(inum);

  int getfile(inum, fileinfo &);
  int getdir(inum, dirinfo &);

  int setattr(inum, size_t);
  int lookup(inum, const char *, bool &, inum &);
  int create(inum, const char *, mode_t, inum &);
  int readdir(inum, std::list<dirent> &);
  int write(inum, size_t, off_t, const char *, size_t &);
  int read(inum, size_t, off_t, std::string &);
  int unlink(inum,const char *);
  int mkdir(inum , const char *, mode_t , inum &);

  int make(inum parent, const char *name, extent_protocol::types type, inum &ino_out);

    /** you may need to add symbolic link related methods here.*/


    bool isSymlink(inum);
    int getSymlink(inum, symlinkinfo &);
    int symlink(const char *, inum, const char *, inum &);
    int readlink(inum, std::string &);
};

#endif
