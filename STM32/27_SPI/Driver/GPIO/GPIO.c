#include "GPIO.h"

void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) {
    if (PinState != GPIO_PIN_RESET)
    {
        GPIOx->BSRR = GPIO_Pin;
    }
    else
    {
        GPIOx->BSRR = (uint32_t)GPIO_Pin << 16u;
    }
}


void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint32_t odr;
    /* get current Output Data Register value */
    odr = GPIOx->ODR;

    /* Set selected pins that were at low level, and reset ones that were high */
    GPIOx->BSRR = ((odr & GPIO_Pin) << GPIO_NUMBER) | (~odr & GPIO_Pin);
}

GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_PinState bitstatus;

    if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
    {
        bitstatus = GPIO_PIN_SET;
    }
    else
    {
        bitstatus = GPIO_PIN_RESET;
    }
    return bitstatus;
}

void HAL_GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
    uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
    uint32_t tmpreg = 0x00, pinmask = 0x00;

    /*---------------------- GPIO ģʽ���� --------------------------*/
      // ���������GPIO_Mode�ĵ���λ�ݴ���currentmode
    currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);

    // bit4��1��ʾ�����bit4��0�������� 
    // �ж�bit4��1����0������ѡ�ж������뻹�����ģʽ
    if ((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
    {
        // ���ģʽ��Ҫ��������ٶ�
        currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed;
    }
    /*-------------GPIO CRL �Ĵ������� CRL�Ĵ��������ŵ�8λIO- -------*/
      // ���ö˿ڵ�8λ����Pin0~Pin7
    if (((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
    {
        // �ȱ���CRL�Ĵ�����ֵ
        tmpreg = GPIOx->CRL;

        // ѭ������Pin0��ʼ��ԣ��ҳ������Pin
        for (pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            // pos��ֵΪ1����pinposλ
            pos = ((uint32_t)0x01) << pinpos;

            // ��pos���������GPIO_PIN��λ�����㣬Ϊ������ж���׼��
            currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

            //��currentpin=pos,���ҵ�ʹ�õ�����
            if (currentpin == pos)
            {
                // pinpos��ֵ������λ������4������Ϊ�Ĵ�����4���Ĵ���λ����һ������
                pos = pinpos << 2;
                //�ѿ���������ŵ�4���Ĵ���λ���㣬�����Ĵ���λ����
                pinmask = ((uint32_t)0x0F) << pos;
                tmpreg &= ~pinmask;

                // ��Ĵ���д�뽫Ҫ���õ����ŵ�ģʽ
                tmpreg |= (currentmode << pos);

                // �ж��Ƿ�Ϊ��������ģʽ
                if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
                {
                    // ��������ģʽ������Ĭ����0����BRR�Ĵ���д1�ɶ�������0
                    GPIOx->BRR = (((uint32_t)0x01) << pinpos);
                }
                else
                {
                    // �ж��Ƿ�Ϊ��������ģʽ
                    if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
                    {
                        // ��������ģʽ������Ĭ��ֵΪ1����BSRR�Ĵ���д1�ɶ�������1
                        GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
                    }
                }
            }
        }
        // ��ǰ�洦�����ݴ�ֵд�뵽CRL�Ĵ���֮��
        GPIOx->CRL = tmpreg;
    }
    /*-------------GPIO CRH �Ĵ������� CRH�Ĵ��������Ÿ�8λIO- -----------*/
      // ���ö˿ڸ�8λ����Pin8~Pin15
    if (GPIO_InitStruct->GPIO_Pin > 0x00FF)
    {
        // // �ȱ���CRH�Ĵ�����ֵ
        tmpreg = GPIOx->CRH;

        // ѭ������Pin8��ʼ��ԣ��ҳ������Pin
        for (pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            pos = (((uint32_t)0x01) << (pinpos + 0x08));

            // pos���������GPIO_PIN��λ������
            currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);

            //��currentpin=pos,���ҵ�ʹ�õ�����
            if (currentpin == pos)
            {
                //pinpos��ֵ������λ������4������Ϊ�Ĵ�����4���Ĵ���λ����һ������
                pos = pinpos << 2;

                //�ѿ���������ŵ�4���Ĵ���λ���㣬�����Ĵ���λ����
                pinmask = ((uint32_t)0x0F) << pos;
                tmpreg &= ~pinmask;

                // ��Ĵ���д�뽫Ҫ���õ����ŵ�ģʽ
                tmpreg |= (currentmode << pos);

                // �ж��Ƿ�Ϊ��������ģʽ
                if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
                {
                    // ��������ģʽ������Ĭ����0����BRR�Ĵ���д1�ɶ�������0
                    GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
                }
                // �ж��Ƿ�Ϊ��������ģʽ
                if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
                {
                    // ��������ģʽ������Ĭ��ֵΪ1����BSRR�Ĵ���д1�ɶ�������1
                    GPIOx->BSRR = (((uint32_t)0x01) << (pinpos + 0x08));
                }
            }
        }
        // ��ǰ�洦�����ݴ�ֵд�뵽CRH�Ĵ���֮��
        GPIOx->CRH = tmpreg;
    }
}


void Hal_GPIO_Mode_Selection(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef Mode) {
    uint8_t Places = (uint8_t)(log2(GPIO_Pin));
    switch (Mode) {
    case GPIO_Mode_AIN:  //ģ��CNF:00  MODE:00
        if (Places >= 8) {
            GPIOx->CRH &= (0x00 << (Places - 8) * 4);
            GPIOx->CRH |= (0x00 << (Places - 8) * 4);
            printf("GPIOx->CRH |= 0x00 << %d\n", (Places - 8) * 4);
        }
        else {
            GPIOx->CRL &= (0x00 << Places * 4);
            GPIOx->CRL |= (0x00 << Places * 4);
            printf("GPIOx->CRL |= 0x00 << %d\n", Places * 4);
        }
        break;
    case GPIO_Mode_IN_FLOATING: //����CNF:01  MODE:00
        if (Places >= 8) {
            GPIOx->CRH &= (0x00 << (Places - 8) * 4);
            GPIOx->CRH |= (0x04 << (Places - 8) * 4);
            printf("GPIOx->CRH |= 0x04 << %d\n", (Places - 8) * 4);
        }
        else {
            GPIOx->CRL &= (0x00 << Places * 4);
            GPIOx->CRL |= (0x04 << Places * 4);
            printf(" GPIOx->CRL |= 0x04 << %d\n", Places * 4);
        }
        break;
    case GPIO_Mode_IPD:     //����CNF:10  MODE:00  ODR=0
        if (Places >= 8) {
            GPIOx->CRH &= (0x00 << (Places - 8) * 4);
            GPIOx->CRH |= (0x08 << (Places - 8) * 4);
            HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
            printf("GPIOx->CRH |= 0x08 << %d\n", (Places - 8) * 4);
        }
        else {
            GPIOx->CRL &= (0x00 << Places * 4);
            GPIOx->CRL |= (0x08 << Places * 4);
            HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
            printf("GPIOx->CRH |= 0x08 << %d\n", Places * 4);
        }
        break;
    case GPIO_Mode_IPU: //����CNF:10  MODE:00 ODR=1
        if (Places >= 8) {
            GPIOx->CRH &= (0x00 << (Places - 8) * 4);
            GPIOx->CRH |= (0x08 << (Places - 8) * 4);
            HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
            printf("GPIOx->CRH |= 0x08 << %d\n", (Places - 8) * 4);
        }
        else {
            GPIOx->CRL &= (0x00 << Places * 4);
            GPIOx->CRL |= (0x08 << Places * 4);
            HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
            printf("GPIOx->CRH |= 0x08 << %d\n", Places * 4);
        }
        break;
    case GPIO_Mode_Out_OD:  // ͨ�ÿ�©01 11
        if (Places >= 8) {
            GPIOx->CRH &= (0x00 << (Places - 8) * 4);
            GPIOx->CRH |= (0x07 << (Places - 8) * 4);
            printf("GPIOx->CRH |= 0x07 << %d\n", (Places - 8) * 4);
        }
        else {
            GPIOx->CRL &= (0x00 << Places * 4);
            GPIOx->CRL |= (0x07 << Places * 4);
            printf("GPIOx->CRH |= 0x07 << %d\n", Places * 4);
        }
        break;
    case GPIO_Mode_Out_PP:  //ͨ������ 00 11
        if (Places >= 8) {
            GPIOx->CRH &= (0x00 << (Places - 8) * 4);
            GPIOx->CRH |= (0x03 << (Places - 8) * 4);
            printf("GPIOx->CRH |= 0x03 << %d\n", (Places - 8) * 4);
        }
        else {
            GPIOx->CRL &= (0x00 << Places * 4);
            GPIOx->CRL |= (0x03 << Places * 4);
            printf("GPIOx->CRH |= 0x03 << %d\n", Places * 4);
        }
        break;
    case GPIO_Mode_AF_OD: //���ÿ�© 11 11
        if (Places >= 8) {
            GPIOx->CRH &= (0x00 << (Places - 8) * 4);
            GPIOx->CRH |= (0x0F << (Places - 8) * 4);
            printf("GPIOx->CRH |= 0x0F << %d\n", (Places - 8) * 4);
        }
        else {
            GPIOx->CRL &= (0x00 << Places * 4);
            GPIOx->CRL |= (0x0F << Places * 4);
            printf("GPIOx->CRH |= 0x0F << %d\n", Places * 4);
        }
        break;
    case GPIO_Mode_AF_PP: //�������� 10 11
        if (Places >= 8) {
            GPIOx->CRH &= (0x00 << (Places - 8) * 4);
            GPIOx->CRH |= (0x0B << (Places - 8) * 4);
            printf("GPIOx->CRH |= 0x0B << %d\n", (Places - 8) * 4);
        }
        else {
            GPIOx->CRL &= (0x00 << Places * 4);
            GPIOx->CRL |= (0x0B << Places * 4);
            printf("GPIOx->CRH |= 0x0B << %d\n", Places * 4);
        }
        break;
    default:
        break;
    }
}
