#ifdef MLFQ
void
scheduler(void)
{
  struct proc *p;
  struct cpu *c = mycpu();
  c->proc = 0;
  int i;
  for(;;)
  {
    //enable interrupts on processor
    sti();

    // Loop over process table looking for process to run.
    acquire(&ptable.lock);
    for(i = 0; i < 4; i++)
    {

        if(front[i] == rear[i] || front[i] == -1) {
            
          continue;
        }
        for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
            
            if(front[i] == rear[i] || front[i] == -1) {
              break;
            }
            if(queue[i][front[i]] == p->pid) {
              if(p->state != RUNNABLE) {
                pop_front(i);
                break;
              }
              pop_front(i);
              p->curr_ticks++;
              p->num_run++;
              
              c->proc = p;
              switchuvm(p);
              p->state = RUNNING;

              swtch(&(c->scheduler), p->context);
              switchkvm();
              c->proc = 0;
              p->ticks[p->level]++;
              p->last_run = ticks;
              // pop_front(i); 
              if(p->curr_ticks >= (1 << i)) {
                p->level++;
                p->curr_ticks = 0;
                
                if(p->state == RUNNABLE)
                  push_back(p->pid, i+1);
              }
              else {
                if(p->state == RUNNABLE) {
                  push_back(p->pid, i);
                }
              }
              // Process is done running for now.
              
            }
          /* Switch to chosen process.  It is the process's job to release ptable.lock and then reacquire it 
            before jumping back to us.
           It should have changed its p->state before coming back.*/
        }
        i = 0;  
        // release(&ptable.lock);
        
    }
    // acquire(&ptable.lock);
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      
      if(p->state != RUNNABLE || p->level != 4)
        continue;

      // Switch to chosen process.  It is the process's job
      // to release ptable.lock and then reacquire it
      // before jumping back to us.
      
      c->proc = p;
      p->num_run++;
      switchuvm(p);
      p->state = RUNNING;

      swtch(&(c->scheduler), p->context);
      switchkvm();

      // Process is done running for now.
      // It should have changed its p->state before coming back.
      c->proc = 0;
      p->ticks[p->level]++;
      p->last_run = ticks;
      
    }
    int j;

    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    {
      
      if(p->state == RUNNABLE && ticks - p->last_run > 1000 && p->level >= 1 && p->level <= 3) {
        for(i = front[p->level]; i < rear[p->level]; i++) {
          if(queue[p->level][i] == p->pid) {
            for(j = i+1; j < rear[p->level]; j++){
              queue[p->level][j-1] = queue[p->level][j];
            }
            
            break;
          }
        }
        rear[p->level]--;
        p->level--;
        push_back(p->pid, p->level);
      }
      else if(p->state == RUNNABLE && p->level == 4 && ticks - p->last_run > 1000) {
        push_back(p->pid, 3);
        
      }
    }
    release(&ptable.lock);

  }
}
#endif