#ifndef __REALVIEW_REG_MMC_H__
#define __REALVIEW_REG_MMC_H__

#include <configs.h>
#include <default.h>

/*
 * prime cell pl181 mci register
 */
#define REALVIEW_MCI_POWER				(0x10005000 + 0x000)
#define REALVIEW_MCI_CLOCK				(0x10005000 + 0x004)
#define REALVIEW_MCI_ARGUMENT			(0x10005000 + 0x008)
#define REALVIEW_MCI_COMMAND			(0x10005000 + 0x00c)

#define REALVIEW_MCI_RESPCMD			(0x10005000 + 0x010)
#define REALVIEW_MCI_RESP0				(0x10005000 + 0x014)
#define REALVIEW_MCI_RESP1				(0x10005000 + 0x018)
#define REALVIEW_MCI_RESP2				(0x10005000 + 0x01c)
#define REALVIEW_MCI_RESP3				(0x10005000 + 0x020)

#define REALVIEW_MCI_DATA_TIMER			(0x10005000 + 0x024)
#define REALVIEW_MCI_DATA_LENGTH		(0x10005000 + 0x028)
#define REALVIEW_MCI_DATA_CTRL			(0x10005000 + 0x02c)
#define REALVIEW_MCI_DATA_CNT			(0x10005000 + 0x030)

#define REALVIEW_MCI_STATUS				(0x10005000 + 0x034)
#define REALVIEW_MCI_CLEAR				(0x10005000 + 0x038)
#define REALVIEW_MCI_MASK0				(0x10005000 + 0x03c)
#define REALVIEW_MCI_MASK1				(0x10005000 + 0x040)
#define REALVIEW_MCI_SELECT				(0x10005000 + 0x044)
#define REALVIEW_MCI_FIFO_CNT			(0x10005000 + 0x048)
#define REALVIEW_MCI_FIFO				(0x10005000 + 0x080)

/*
 * bit masks for command
 */
#define REALVIEW_MCI_CMD_RESPONSE		(1 << 6)
#define REALVIEW_MCI_CMD_LONGRSP		(1 << 7)
#define REALVIEW_MCI_CMD_INTERRUPT		(1 << 8)
#define REALVIEW_MCI_CMD_PENDING		(1 << 9)
#define REALVIEW_MCI_CMD_ENABLE			(1 << 10)

/*
 * bit masks for status
 */
#define	REALVIEW_MCI_STAT_CMD_CRC_FAIL	(1 << 0)
#define	REALVIEW_MCI_STAT_DAT_CRC_FAIL  (1 << 1)
#define	REALVIEW_MCI_STAT_CMD_TIME_OUT  (1 << 2)
#define	REALVIEW_MCI_STAT_DAT_TIME_OUT  (1 << 3)
#define	REALVIEW_MCI_STAT_TX_UNDERRUN	(1 << 4)
#define	REALVIEW_MCI_STAT_RX_OVERRUN	(1 << 5)
#define	REALVIEW_MCI_STAT_CMD_RESP_END	(1 << 6)
#define	REALVIEW_MCI_STAT_CMD_SENT		(1 << 7)
#define	REALVIEW_MCI_STAT_DAT_END		(1 << 8)
#define	REALVIEW_MCI_STAT_DAT_BLK_END	(1 << 10)
#define	REALVIEW_MCI_STAT_CMD_ACT		(1 << 11)
#define	REALVIEW_MCI_STAT_TX_ACT		(1 << 12)
#define	REALVIEW_MCI_STAT_RX_ACT		(1 << 13)
#define	REALVIEW_MCI_STAT_TX_FIFO_HALF	(1 << 14)
#define	REALVIEW_MCI_STAT_RX_FIFO_HALF	(1 << 15)
#define	REALVIEW_MCI_STAT_TX_FIFO_FULL	(1 << 16)
#define	REALVIEW_MCI_STAT_RX_FIFO_FULL	(1 << 17)
#define	REALVIEW_MCI_STAT_TX_FIFO_ZERO	(1 << 18)
#define	REALVIEW_MCI_STAT_RX_DAT_ZERO	(1 << 19)
#define	REALVIEW_MCI_STAT_TX_DAT_AVL	(1 << 20)
#define	REALVIEW_MCI_STAT_RX_FIFO_AVL	(1 << 21)

/*
 * bit masks for clear status
 */
#define REALVIEW_MCI_CLR_CMD_CRC_FAIL	(1 << 0)
#define REALVIEW_MCI_CLR_DAT_CRC_FAIL	(1 << 1)
#define REALVIEW_MCI_CLR_CMD_TIMEOUT	(1 << 2)
#define REALVIEW_MCI_CLR_DAT_TIMEOUT	(1 << 3)
#define REALVIEW_MCI_CLR_TX_UNDERRUN	(1 << 4)
#define REALVIEW_MCI_CLR_RX_OVERRUN		(1 << 5)
#define REALVIEW_MCI_CLR_CMD_RESP_END	(1 << 6)
#define REALVIEW_MCI_CLR_CMD_SENT		(1 << 7)
#define REALVIEW_MCI_CLR_DAT_END		(1 << 8)
#define REALVIEW_MCI_CLR_DAT_BLK_END	(1 << 10)

#endif /* __REALVIEW_REG_MMC_H__ */
