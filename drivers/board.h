/**************************************************************************************************
 * board.h
 * @brief Specification/Implementation file
 **************************************************************************************************
 * $Revision$
 * $LastChangedDate$
 * $Author$
 **************************************************************************************************/

#ifndef BOARD_H_
#define BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

struct Board {
  int empty;
};

void ConfigSystemClock(void);
void InitGPIOs(void);
void InitSPIs(void);
void BlinkLEDs(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */
