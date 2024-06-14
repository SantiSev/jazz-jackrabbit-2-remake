/*
 * Este codigo se encuentra bajo licencia: GPL v2
 * El autor del mismo es: Taller de programacion I (Veiga) FIUBA (eldipa)
 * El link al repositorio es: https://github.com/eldipa/sockets-en-cpp
 * */

#include "common_resolvererror.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>

ResolverError::ResolverError(int gai_errno): gai_errno(gai_errno) {}

const char* ResolverError::what() const noexcept { return gai_strerror(gai_errno); }

ResolverError::~ResolverError() {}
