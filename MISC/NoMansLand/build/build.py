import git # Gitpython
import os
import random
import string

random.seed(98562)

flag_text = open("flag.txt", "r").read()

os.system('rm -rf NoMansLand/ NoMansLand.zip')
os.mkdir("NoMansLand")
os.chdir("NoMansLand")

with git.Repo.init(path='.') as repo:
    def commit():
        msg = ''.join([random.choice(string.ascii_letters) for _ in range(48)])
        return repo.index.commit(msg)

    config = repo.config_writer()
    config.set_value("user", "name", "xp0int")
    config.set_value("user", "email", "welcome.to@xp0int.top")
    config.release()

    for i in range(0, len(flag_text) + 1):
        with open("flag.txt", "w") as fp:
            fp.write(flag_text[:i])
        repo.index.add(items=['flag.txt'])
        commit()

    print 'Flag commit:', str(repo.head.reference.log()[-1]).split(' ')[0]

    for i in range(len(flag_text) - 1, -1, -1):
        with open("flag.txt", "w") as fp:
            fp.write(flag_text[:i])
        repo.index.add(items=['flag.txt'])
        commit()

    repo.index.remove(items=['flag.txt'])
    os.unlink("flag.txt")
    commit()

os.chdir("..")
os.system("zip -rq NoMansLand.zip NoMansLand/")

