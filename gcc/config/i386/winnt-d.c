/* Windows support needed only by D front-end.
   Copyright (C) 2021 Free Software Foundation, Inc.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#define IN_TARGET_CODE 1

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "target.h"
#include "d/d-target.h"
#include "d/d-target-def.h"
#include "tm_p.h"

/* Implement TARGET_D_OS_VERSIONS for Windows targets.  */

static void
winnt_d_os_builtins (void)
{
  d_add_builtin_version ("Windows");

#define builtin_version(TXT) d_add_builtin_version (TXT)

#ifdef EXTRA_TARGET_D_OS_VERSIONS
  EXTRA_TARGET_D_OS_VERSIONS ();
#endif
}

/* Handle a call to `__traits(getTargetInfo, "objectFormat")'.  */

static tree
winnt_d_handle_target_object_format (void)
{
  const char *objfmt = "coff";

  return build_string_literal (strlen (objfmt) + 1, objfmt);
}

/* Implement TARGET_D_REGISTER_OS_TARGET_INFO for Windows targets.  */

static void
winnt_d_register_target_info (void)
{
  const struct d_target_info_spec handlers[] = {
    { "objectFormat", winnt_d_handle_target_object_format },
    { NULL, NULL },
  };

  d_add_target_info_handlers (handlers);
}
#undef TARGET_D_OS_VERSIONS
#define TARGET_D_OS_VERSIONS winnt_d_os_builtins

#undef TARGET_D_REGISTER_OS_TARGET_INFO
#define TARGET_D_REGISTER_OS_TARGET_INFO winnt_d_register_target_info

/* Define TARGET_D_MINFO_SECTION for Windows targets.  */

#undef TARGET_D_MINFO_SECTION
#define TARGET_D_MINFO_SECTION "minfo"

#undef TARGET_D_MINFO_START_NAME
#define TARGET_D_MINFO_START_NAME "__start_minfo"

#undef TARGET_D_MINFO_END_NAME
#define TARGET_D_MINFO_END_NAME "__stop_minfo"

/* Define TARGET_D_TEMPLATES_ALWAYS_COMDAT for Windows targets.  */

#undef TARGET_D_TEMPLATES_ALWAYS_COMDAT
#define TARGET_D_TEMPLATES_ALWAYS_COMDAT true

struct gcc_targetdm targetdm = TARGETDM_INITIALIZER;
