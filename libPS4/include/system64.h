/*
 *  this file was mostly taken out of the internet here:
 *  http://lxr.free-electrons.com/source/include/asm-x86/system_64.h?v=2.6.24
 *
 *  I just swapped some asm moveq instructions to make it work for the PS4.
 *  
 */

#ifndef SYSTEM64_H
#define SYSTEM64_H

#include <ps4.h>

#define nop() __asm__ __volatile__ ("nop")                          // No Operation.
#define cli() __asm__ __volatile__ ("cli")                          // Disable interrrupts.
#define sti() __asm__ __volatile__ ("sti")                          // Enable interrupts.
#define hlt() __asm__ __volatile__ ("hlt")                          // Turn CPU into HALT state (power saving mode C1).
#define stp() __asm__ __volatile__ (sti() hlt() : : : "memory")     // Turn CPU into STOP.
#define clts() __asm__ __volatile__ ("clts")                        // Clear 'TS' bit respectively.
#define stts() write_cr0(8 | read_cr0())                            // Set 'TS' bit.
#define wbinvd() __asm__ __volatile__ ("wbinvd": : :"memory")       // Flush the L1 cache without losing information. ("Write Back and Invalidate")

// Read the value of write protection and return it.
static inline uint64_t read_cr0(void)
{
	uint64_t cr0;
	asm volatile ("movq %0, %%cr0;" : "=r" (cr0) : : "memory");
	return cr0;
}

// Write a value to the write protection.
static inline void write_cr0(uint64_t cr0)
{
	asm volatile ("movq %%cr0, %0;" :: "r" (cr0) : "memory");
}

static inline uint64_t read_cr2(void)
{
  uint64_t cr2;
  asm volatile("movq %0, %%cr2" : "=r" (cr2));
  return cr2;
}

static inline void write_cr2(uint64_t val)
{
  asm volatile("movq %%cr2, %0" :: "r" (val));
}

static inline uint64_t read_cr3(void)
{ 
  uint64_t cr3;
  asm volatile("movq %0, %%cr3" : "=r" (cr3));
  return cr3;
}
 
static inline void write_cr3(uint64_t val)
{
  asm volatile("movq %%cr3, %0" :: "r" (val) : "memory");
}
 
static inline uint64_t read_cr4(void)
{ 
  uint64_t cr4;
  asm volatile("movq %0, %%cr4" : "=r" (cr4));
  return cr4;
}
 
static inline void write_cr4(uint64_t val)
{ 
  asm volatile("movq %%cr4, %0" :: "r" (val) : "memory");
}
 
static inline uint64_t read_cr8(void)
{
  uint64_t cr8;
  asm volatile("movq %0, %%cr8" : "=r" (cr8));
  return cr8;
}
 
static inline void write_cr8(uint64_t val)
{
  asm volatile("movq %%cr8, %0" :: "r" (val) : "memory");
}

#endif
