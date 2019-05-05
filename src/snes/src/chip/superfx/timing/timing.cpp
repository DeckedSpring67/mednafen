#ifdef SUPERFX_CPP

void SuperFX::add_clocks(unsigned clocks) {
  if(regs.romcl) {
    regs.romcl -= min(clocks, regs.romcl);
    if(regs.romcl == 0) {
      regs.sfr.r = 0;
      regs.romdr = superfxbus.read((regs.rombr << 16) + regs.r[14]);
    }
  }

  if(regs.ramcl) {
    regs.ramcl -= min(clocks, regs.ramcl);
    if(regs.ramcl == 0) {
      superfxbus.write(0x700000 + (regs.rambr << 16) + regs.ramar, regs.ramdr);
    }
  }

  scheduler.addclocks_cop(clocks);
  scheduler.sync_copcpu();
}

void SuperFX::rombuffer_sync() {
  if(regs.romcl) add_clocks(regs.romcl);
}

alwaysinline void SuperFX::rombuffer_update() {
  regs.sfr.r = 1;
  regs.romcl = memory_access_speed;
}

alwaysinline uint8 SuperFX::rombuffer_read() {
  rombuffer_sync();
  return regs.romdr;
}

void SuperFX::rambuffer_sync() {
  if(regs.ramcl) add_clocks(regs.ramcl);
}

uint8 SuperFX::rambuffer_read(uint16 addr) {
  rambuffer_sync();
  return superfxbus.read(0x700000 + (regs.rambr << 16) + addr);
}

void SuperFX::rambuffer_write(uint16 addr, uint8 data) {
  rambuffer_sync();
  regs.ramcl = memory_access_speed;
  regs.ramar = addr;
  regs.ramdr = data;
}

static void SuperFX_r14_modify(uint16 data)
{
 superfx.rombuffer_update();
}

static void SuperFX_r15_modify(uint16 data)
{
 superfx.r15_NOT_modified = !true;
}

void SuperFX::update_speed() {
  //force SuperFX1 mode?
  if(clockmode == 1) {
    cache_access_speed  = 2;
    memory_access_speed = 6;
    return;
  }

  //force SuperFX2 mode?
  if(clockmode == 2) {
    cache_access_speed  = 1;
    memory_access_speed = 5;
    regs.cfgr.ms0 = 0;  //cannot use high-speed multiplication in 21MHz mode
    return;
  }

  //default: allow S-CPU to select mode
  cache_access_speed  = (regs.clsr ? 1 : 2);
  memory_access_speed = (regs.clsr ? 5 : 6);
  if(regs.clsr) regs.cfgr.ms0 = 0;  //cannot use high-speed multiplication in 21MHz mode
}

void SuperFX::timing_reset() {
  update_speed();
  r15_NOT_modified = !false;

  regs.romcl = 0;
  regs.romdr = 0;

  regs.ramcl = 0;
  regs.ramar = 0;
  regs.ramdr = 0;
}

#endif
