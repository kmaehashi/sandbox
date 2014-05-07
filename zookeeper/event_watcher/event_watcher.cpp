#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#include <zookeeper/zookeeper.h>

/* Partially quoted from ZooKeeper src/c/src/cli.c */

static const char* state2String(int state){
  if (state == 0)
    return "CLOSED_STATE";
  if (state == ZOO_CONNECTING_STATE)
    return "CONNECTING_STATE";
  if (state == ZOO_ASSOCIATING_STATE)
    return "ASSOCIATING_STATE";
  if (state == ZOO_CONNECTED_STATE)
    return "CONNECTED_STATE";
  if (state == ZOO_EXPIRED_SESSION_STATE)
    return "EXPIRED_SESSION_STATE";
  if (state == ZOO_AUTH_FAILED_STATE)
    return "AUTH_FAILED_STATE";

  return "INVALID_STATE";
}

static const char* type2String(int state){
  if (state == ZOO_CREATED_EVENT)
    return "CREATED_EVENT";
  if (state == ZOO_DELETED_EVENT)
    return "DELETED_EVENT";
  if (state == ZOO_CHANGED_EVENT)
    return "CHANGED_EVENT";
  if (state == ZOO_CHILD_EVENT)
    return "CHILD_EVENT";
  if (state == ZOO_SESSION_EVENT)
    return "SESSION_EVENT";
  if (state == ZOO_NOTWATCHING_EVENT)
    return "NOTWATCHING_EVENT";

  return "UNKNOWN_EVENT_TYPE";
}

void watcher(zhandle_t *zzh, int type, int state, const char *path,
             void* context) {
  fprintf(stdout, "Watcher %s(%d) state = %s(%d)", type2String(type), type, state2String(state), state);
  if (path && strlen(path) > 0) {
    fprintf(stdout, " for path %s", path);
  }
  fprintf(stdout, "\n");
}

int main(int argc, char** argv) {
  zoo_set_debug_level(ZOO_LOG_LEVEL_DEBUG);
  zoo_deterministic_conn_order(1);
  zhandle_t *zh = zookeeper_init(argv[1], watcher, 30000, 0, 0, 0);

  int state = 0;
  while(state != ZOO_CONNECTED_STATE) {
    state = zoo_state(zh);
    fprintf(stdout, "Waiting: state = %s(%d)\n", state2String(state), state);
    ::sleep(1);
  }
  char buf[16];
  int ret;
  ret = zoo_create(zh, "/test", "value", 5, &ZOO_OPEN_ACL_UNSAFE, ZOO_EPHEMERAL, buf, 16);
  if (ret != ZOK) {
    fprintf(stdout, "zoo_create failed with error %d\n", ret);
    ::exit(1);
  }
  ::sleep(-1); // sleep forever
}
