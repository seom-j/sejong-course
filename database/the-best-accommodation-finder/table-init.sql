-- 외래키 설정
ALTER TABLE detail_info
ADD FOREIGN kEY detail_info(Aid)
REFERENCES basic_info(Aid);

ALTER TABLE review_info
ADD FOREIGN kEY review_info(Aid)
REFERENCES basic_info(Aid);

-- location_info, type_info table 생성
CREATE TABLE location_info AS SELECT DISTINCT location FROM basic_info;

CREATE TABLE type_info AS SELECT DISTINCT Type FROM basic_info;
