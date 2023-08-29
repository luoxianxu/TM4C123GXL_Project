#include "myAdc.h"

void ADC_Config(void){
	//ʱ��ʹ��
	SysCtlPeripheralEnable(ADC_SYSCTL_PERIPH);
	SysCtlPeripheralEnable(ADCGPIO_SYSCTL_PERIPH);
	//GPIO����
	GPIOPinTypeADC(ADC_GPIO, ADC_GPIO_Pin);
	//
    ADCSequenceConfigure(ADC, SequenceNum, ADC_TRIGGER_PROCESSOR, Priority);
    ADCSequenceStepConfigure(ADC, SequenceNum, Priority, ADC_CTL_D | ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC, SequenceNum);
	
	ADCIntEnable(ADC, SequenceNum);
    IntEnable(ADC_INT);
    IntMasterEnable();
    ADCIntClear(ADC, SequenceNum);

}

void ADCGetValueHandler(void){		//�жϻ�ȡ����
	uint32_t pui32ADC0Value[1];
	ADCIntClear(ADC0_BASE, SequenceNum);
	ADCSequenceDataGet(ADC0_BASE, SequenceNum, pui32ADC0Value);
	UARTprintf("%d\r\n",pui32ADC0Value[0]);
}

