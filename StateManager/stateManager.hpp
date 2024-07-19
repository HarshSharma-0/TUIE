#ifndef STATEMANAGER_H
#define STATEMANAGER_H

typedef int (*onPress)();
// typedef int()();

class stateManagerButton {
public:
  stateManagerButton(char *_ID) { ID = _ID; }
  void regesterPress(onPress _stat) { onClick = _stat; }

private:
  char *ID = nullptr;
  onPress onClick = nullptr;
};

class stateManagerView {
public:
private:
};

class stateManagerProgress {
public:
private:
};

class stateManagerList {
public:
private:
};

#endif
