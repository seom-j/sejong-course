-- 최종 랭킹 순으로 상세 정보 제공
SELECT d.*
FROM detail_info AS d
INNER JOIN want_info AS w ON d.Aid = w.Aid
ORDER BY w.FinalParameter ASC;
-- 벤티모 호텔 앤 레지던스 제주 ! 에약 완료 !
