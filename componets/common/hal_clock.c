#include "ht66F2390.h"
#include "defs.h"
#include "hal_clock.h"

void clockSetSystemSrc(uint8_t source ,uint8_t hz ,uint8_t div)
{
	if(source == CLOCK_SCC_FHS_HIRC)	//內部
	{
		_scc = _scc & ~(CLOCK_SCC_FHS_STATUS << 3);		//把它取消
		_scc = _scc | (source << 3);		//致能
		
		_hircc = _hircc & ~(CLOCK_HIRCC_HIRC_STATUS << 2);
		_hircc = _hircc | (hz << 2);
		
		/*_hircc = _hircc & ~(CLOCK_HIRCC_HIRCEN_STATUS);
		_hircc = _hircc  | CLOCK_HIRCC_HIRCEN_ENABLE;*/
		
		_scc  = _scc & ~(CLOCK_SCC_CKS_STATUS << 5);
		_scc  = _scc | (div << 5);
	}
	
	else if(source == CLOCK_SCC_FHS_HXT)	//外部
	{
		_scc = _scc & ~(CLOCK_SCC_FHS_STATUS << 3);		//把它取消
		_scc = _scc | (source << 3);		//致能
		
		_hxtc = _hircc & ~(CLOCK_HXTC_HXTM_STATUS << 2);
		_hxtc = _hircc | (hz << 2);
		
		_hxtc = _hxtc & ~(CLOCK_HXTC_HXTEN_STATUS);
		_hxtc = _hxtc | CLOCK_HXTC_HXTEN_ENABLE;
		
		_scc  = _scc & ~(CLOCK_SCC_CKS_STATUS << 5);
		_scc  = _scc | (div << 5);
	}
}


	//----時脈暫存器----
	/*_scc = 0x17;
	_hircc= 0x09;
	_hxtc = 0x00;
	_lxtc = 0x00;*/
	//------------------
