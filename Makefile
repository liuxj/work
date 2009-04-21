#
# (C) Copyright  2009 
# Author: xiangjun liu <liuxiangj@gmail.com>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 3 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA  02110-1301, USA

RM = rm -f
CC = gcc
LD = ld
CFLAGS = -g -O3 -Wall -I.

TARGETS = work
OBJS = finished.o

all: $(TARGETS)
work: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.c.o: 
	$(CC) $(CFLAGS) -c $< -o $@

clean::
	$(RM) $(TARGETS) *.o *.d 

-include $(wildcard *.d) dummy  
